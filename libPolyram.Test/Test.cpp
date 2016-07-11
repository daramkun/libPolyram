#define POLYRAM_D3D12
#include "polyram.h"
#include "polyram_d3d11.h"

struct MyConstantBuffer { PRMat world, proj; };

class MyScene : public PRGame
{
public:
	/*ID3D11Texture2D * texture;
	ID3D11ShaderResourceView * textureSRV;
	PRDraw2DUtility * draw2DUtil;
	ID3D11RasterizerState * rasterizerState;*/

public:
	void onInitialize ()
	{
		/*GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		texture = PRCreateTexture2D ( graphicsContext->d3dDevice, std::string ( "Test1.jpg" ) );
		graphicsContext->d3dDevice->CreateShaderResourceView ( texture, nullptr, &textureSRV );

		draw2DUtil = new PRDraw2DUtility ( graphicsContext->d3dDevice );

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset ( &rasterizerDesc, 0, sizeof ( D3D11_RASTERIZER_DESC ) );
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		graphicsContext->d3dDevice->CreateRasterizerState ( &rasterizerDesc, &rasterizerState );*/
	}

	void onDestroy ()
	{
		/*rasterizerState->Release ();
		SAFE_DELETE ( draw2DUtil );
		textureSRV->Release ();
		texture->Release ();*/
	}

	void onDraw ( double dt )
	{
		/*GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		float clearColor [] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView ( graphicsContext->renderTargetView, clearColor );
		graphicsContext->immediateContext->ClearDepthStencilView ( graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0 );

		graphicsContext->immediateContext->RSSetState ( rasterizerState );

		draw2DUtil->SetResolution ( 1280, 720 );
		draw2DUtil->Ready ( graphicsContext->immediateContext );
		draw2DUtil->Draw ( graphicsContext->immediateContext, textureSRV, PRMat () );*/
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D12 );

		graphicsContext->dxgiSwapChain->Present ( 1, 0 );
		graphicsContext->Synchronization ();
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME ( MAIN_FUNC_ARGS )
{
	try {
		MyScene scene;
		std::string title ( "Test" );
		PRApp app ( &scene, PRRendererType_Direct3D12, 1280, 720, title );
		app.run ();
	}
	catch ( std::exception & ex ) {
		PRLog ( ex.what () );
	}
}