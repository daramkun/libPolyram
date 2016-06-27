#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"
#include <vector>
#include <thread>

struct MyConstantBuffer { PRMat world, view, proj; PRVec4 col; };

class MyScene : public PRGame
{
public:
	ID3D11Buffer * sphereVB;
	int sphereVBSize;
	ID3D11InputLayout * inputLayout;
	ID3D11VertexShader * vertexShader;
	ID3D11PixelShader * pixelShader;
	ID3D11Buffer * vertexCB;
	ID3D11RasterizerState * rasterizerState;

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		PRModelGenerator sphere ( PRModelType_Sphere, PRModelProperty_Position );
		sphereVB = PRCreateVertexBuffer ( graphicsContext->d3dDevice, sphere.getData (), sphere.getDataSize () );
		sphereVBSize = sphere.getDataSize () / sizeof ( PRVec3 );

		D3D11_INPUT_ELEMENT_DESC inputElements [] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		PRLoadShader ( graphicsContext->d3dDevice, std::string ( "MyVertexShader.cso" ), std::string ( "MyPixelShader.cso" ),
			&vertexShader, &pixelShader, inputElements, _countof ( inputElements ), &inputLayout );

		vertexCB = PRCreateConstantBuffer<MyConstantBuffer> ( graphicsContext->d3dDevice, true );

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset ( &rasterizerDesc, 0, sizeof ( D3D11_RASTERIZER_DESC ) );
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.DepthClipEnable = false;
		graphicsContext->d3dDevice->CreateRasterizerState ( &rasterizerDesc, &rasterizerState );
	}

	void onDestroy ()
	{
		rasterizerState->Release ();
		vertexCB->Release ();
		pixelShader->Release ();
		vertexShader->Release ();
		inputLayout->Release ();
		sphereVB->Release ();
	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		float clearColor [] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView ( graphicsContext->renderTargetView, clearColor );
		graphicsContext->immediateContext->ClearDepthStencilView ( graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0 );

		//std::vector<ID3D11CommandList*> commandLists;
		ID3D11CommandList* commandLists [ 8 ] = { 0, };
		std::thread independentThread ( [ & ] ()
		{
#pragma omp parallel for
			for ( int i = 0; i < 8; ++i )
			{
				ID3D11DeviceContext * deferredContext;
				graphicsContext->d3dDevice->CreateDeferredContext ( 0, &deferredContext );

				deferredContext->OMSetRenderTargets ( 1, &graphicsContext->renderTargetView, graphicsContext->depthStencilView );

				D3D11_VIEWPORT viewport = { 0, };
				viewport.Width = 1280;
				viewport.Height = 720;
				viewport.MaxDepth = 1;
				deferredContext->RSSetViewports ( 1, &viewport );

				deferredContext->VSSetShader ( vertexShader, nullptr, 0 );
				deferredContext->PSSetShader ( pixelShader, nullptr, 0 );

				deferredContext->VSSetConstantBuffers ( 0, 1, &vertexCB );

				deferredContext->RSSetState ( rasterizerState );

				unsigned stride = sizeof ( PRVec3 ), offset = 0;
				deferredContext->IASetVertexBuffers ( 0, 1, &sphereVB, &stride, &offset );
				deferredContext->IASetPrimitiveTopology ( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
				deferredContext->IASetInputLayout ( inputLayout );

				for ( int i = 0; i < 20000 / 8; ++i )
				{
					MyConstantBuffer cb;
					PRMat::createTranslate ( &PRVec3 ( -0.5f, 0, 0 ), &cb.world );
					PRMat::createLookAtLH ( &PRVec3 ( 0, 0, 1 ), &PRVec3 ( 0, 0, 0 ), &PRVec3 ( 0, 1, 0 ), &cb.view );
					PRMat::createPerspectiveFieldOfViewLH ( PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb.proj );
					cb.col = PRVec4 ( 1, 1, 1, 1 );
					D3D11_MAPPED_SUBRESOURCE mappedResource;
					if ( deferredContext->Map ( vertexCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource ) == S_OK )
					{
						memcpy ( mappedResource.pData, &cb, sizeof ( MyConstantBuffer ) );
						deferredContext->Unmap ( vertexCB, 0 );
					}

					deferredContext->Draw ( sphereVBSize, 0 );
				}

				ID3D11CommandList * commandList;
				deferredContext->FinishCommandList ( false, &commandList );
				//commandLists.push_back ( commandList );
				commandLists [ i ] = commandList;

				deferredContext->Release ();
			}
		} );
		independentThread.join ();

		//for ( auto i = commandLists.begin (); i != commandLists.end (); ++i )
		for ( int i = 0; i < 8; ++i )
		{
			graphicsContext->immediateContext->ExecuteCommandList ( commandLists [ i ], false );
			commandLists [ i ]->Release ();
		}

		// Present
		graphicsContext->dxgiSwapChain->Present ( 0, 0 );
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME ( MAIN_FUNC_ARGS )
{
	try {
		MyScene scene;
		std::string title ( "Test" );
		PRApp app ( &scene, PRRendererType_Direct3D11, 1280, 720, title );
		app.run ();
	}
	catch ( std::exception & ex ) {
		PRLog ( ex.what () );
	}
}