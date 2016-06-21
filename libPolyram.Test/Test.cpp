#define POLYRAM_D3D11
#include "polyram.h"

class MyScene : public PRGame
{
public:
	ID3D11Buffer * vertexBuffer;
	ID3D11InputLayout * inputLayout;
	ID3D11VertexShader * vertexShader;
	ID3D11PixelShader * pixelShader;
	ID3D11Texture2D * texture;
	ID3D11ShaderResourceView * textureSRV;

	ID3D11RenderTargetView * renderTarget;
	ID3D11Texture2D * renderTargetBuffer;
	ID3D11ShaderResourceView * renderTargetBufferSRV;
	ID3D11SamplerState * samplerState;
	ID3D11VertexShader * renderTargetVertexShader;
	ID3D11PixelShader * renderTargetPixelShader;
	ID3D11InputLayout * renderTargetInputLayout;
	ID3D11Buffer * renderTargetConstantBuffer;
	ID3D11DepthStencilState * depthStencilState;
	ID3D11RasterizerState * rasterizerState;

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		PRModelGenerator rect ( PRModelType_Rectangle, PRModelProperty_Position | PRModelProperty_TexCoord );
		D3D11_BUFFER_DESC vertexBufferDesc = { rect.getDataSize (), D3D11_USAGE_DEFAULT,
			D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
		D3D11_SUBRESOURCE_DATA vertexBufferInput = { rect.getData (), rect.getDataSize () };
		graphicsContext->d3dDevice->CreateBuffer ( &vertexBufferDesc, &vertexBufferInput, &vertexBuffer );

		void * shaderData;
		unsigned shaderDataLength;
		PRGetRawData ( std::string ( "MyVertexShader.cso" ), &shaderData, &shaderDataLength );
		graphicsContext->d3dDevice->CreateVertexShader ( shaderData, shaderDataLength, nullptr, &vertexShader );
		D3D11_INPUT_ELEMENT_DESC inputElements [] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		graphicsContext->d3dDevice->CreateInputLayout ( inputElements, _countof ( inputElements ),
			shaderData, shaderDataLength, &inputLayout );
		SAFE_DELETE ( shaderData );

		PRGetRawData ( std::string ( "MyPixelShader.cso" ), &shaderData, &shaderDataLength );
		graphicsContext->d3dDevice->CreatePixelShader ( shaderData, shaderDataLength, nullptr, &pixelShader );
		SAFE_DELETE ( shaderData );

		void * textureData;
		unsigned textureWidth, textureHeight;
		PRGetImageData ( std::string ( "test.jpg" ), &textureData, &textureWidth, &textureHeight );

		D3D11_TEXTURE2D_DESC textureDesc = { 0, };
		textureDesc.ArraySize = 1;
		textureDesc.Width = textureWidth;
		textureDesc.Height = textureHeight;
		textureDesc.MipLevels = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		D3D11_SUBRESOURCE_DATA textureSubResource = { textureData, textureWidth * sizeof ( int ),
			textureWidth * textureHeight * sizeof ( int ) };
		graphicsContext->d3dDevice->CreateTexture2D ( &textureDesc, &textureSubResource, &texture );

		delete [] textureData;

		graphicsContext->d3dDevice->CreateShaderResourceView ( texture, nullptr, &textureSRV );

		D3D11_TEXTURE2D_DESC renderTargetDesc = { 0, };
		renderTargetDesc.ArraySize = 1;
		renderTargetDesc.Width = 1280;
		renderTargetDesc.Height = 720;
		renderTargetDesc.MipLevels = 1;
		renderTargetDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderTargetDesc.SampleDesc.Count = 1;
		renderTargetDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		renderTargetDesc.Usage = D3D11_USAGE_DEFAULT;
		renderTargetDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		graphicsContext->d3dDevice->CreateTexture2D ( &renderTargetDesc, nullptr, &renderTargetBuffer );

		graphicsContext->d3dDevice->CreateRenderTargetView ( renderTargetBuffer, nullptr, &renderTarget );

		graphicsContext->d3dDevice->CreateShaderResourceView ( renderTargetBuffer, nullptr, &renderTargetBufferSRV );

		D3D11_SAMPLER_DESC samplerDesc;
		memset ( &samplerDesc, 0, sizeof ( D3D11_SAMPLER_DESC ) );
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		graphicsContext->d3dDevice->CreateSamplerState ( &samplerDesc, &samplerState );

		PRGetRawData ( std::string ( "MyVertexShaderRT.cso" ), &shaderData, &shaderDataLength );
		graphicsContext->d3dDevice->CreateVertexShader ( shaderData, shaderDataLength, nullptr, &renderTargetVertexShader );
		D3D11_INPUT_ELEMENT_DESC inputElementsRT [] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		graphicsContext->d3dDevice->CreateInputLayout ( inputElementsRT, _countof ( inputElementsRT ),
			shaderData, shaderDataLength, &renderTargetInputLayout );
		SAFE_DELETE ( shaderData );

		PRGetRawData ( std::string ( "MyPixelShaderRT.cso" ), &shaderData, &shaderDataLength );
		graphicsContext->d3dDevice->CreatePixelShader ( shaderData, shaderDataLength, nullptr, &renderTargetPixelShader );
		SAFE_DELETE ( shaderData );

		D3D11_BUFFER_DESC constantBufferDesc = { 0, };
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = sizeof ( PRMat ) * 2;
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		graphicsContext->d3dDevice->CreateBuffer ( &constantBufferDesc, nullptr, &renderTargetConstantBuffer );

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0, };
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		graphicsContext->d3dDevice->CreateDepthStencilState ( &depthStencilDesc, &depthStencilState );

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset ( &rasterizerDesc, 0, sizeof ( D3D11_RASTERIZER_DESC ) );
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.DepthClipEnable = false;
		rasterizerDesc.FrontCounterClockwise = false;
		graphicsContext->d3dDevice->CreateRasterizerState ( &rasterizerDesc, &rasterizerState );
	}

	void onDestroy ()
	{
		rasterizerState->Release ();
		depthStencilState->Release ();
		renderTargetConstantBuffer->Release ();
		renderTargetInputLayout->Release ();
		renderTargetPixelShader->Release ();
		renderTargetVertexShader->Release ();
		samplerState->Release ();
		renderTargetBufferSRV->Release ();
		renderTarget->Release ();
		renderTargetBuffer->Release ();
		textureSRV->Release ();
		texture->Release ();
		pixelShader->Release ();
		vertexShader->Release ();
		inputLayout->Release ();
		vertexBuffer->Release ();
	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );

		float clearColor [] = { 1, 0, 1, 1 };
		ID3D11ShaderResourceView * pSRV [] = { nullptr };
		graphicsContext->immediateContext->PSSetShaderResources ( 0, 1, pSRV );
		graphicsContext->immediateContext->OMSetRenderTargets ( 1, &renderTarget, nullptr );
		graphicsContext->immediateContext->ClearRenderTargetView ( renderTarget, clearColor );

		graphicsContext->immediateContext->VSSetShader ( vertexShader, nullptr, 0 );
		graphicsContext->immediateContext->PSSetShader ( pixelShader, nullptr, 0 );
		graphicsContext->immediateContext->PSSetShaderResources ( 0, 1, &textureSRV );
		graphicsContext->immediateContext->PSSetSamplers ( 0, 1, &samplerState );

		unsigned stride = sizeof ( PRVec3 ) + sizeof ( PRVec2 ), offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers ( 0, 1, &vertexBuffer, &stride, &offset );
		graphicsContext->immediateContext->IASetPrimitiveTopology ( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		graphicsContext->immediateContext->IASetInputLayout ( inputLayout );

		graphicsContext->immediateContext->OMSetDepthStencilState ( nullptr, 1 );

		graphicsContext->immediateContext->Draw ( 6, 0 );

		float clearColor1 [] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->OMSetRenderTargets ( 1, &graphicsContext->renderTargetView, nullptr );
		graphicsContext->immediateContext->ClearRenderTargetView ( graphicsContext->renderTargetView, clearColor1 );

		struct { PRMat world; PRMat proj; } cb;
		PRMat temp;
		PRMat::createTranslate ( &PRVec3 ( 0.5f, 0.5f ), &cb.world );
		PRMat::createScale ( &PRVec3 ( 1280, 720, 1 ), &temp );
		cb.world = PRMat::multiply ( cb.world, temp );
		//PRMat::createTranslate ( &PRVec3 ( 0.5f, 0.5f ), &cb.world );
		//PRMat::createScale ( &PRVec3 ( 1280, 720, 1 ), &cb.world );
		PRMat::createOrthographicOffCenterLH ( 0, 1280, 720, 0, 0.001f, 1000.0f, &cb.proj );
		//PRMat::createPerspectiveFieldOfViewLH ( PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb.proj );
		//cb.world = cb.world.transpose ();
		//cb.proj = cb.proj.transpose ();
		graphicsContext->immediateContext->UpdateSubresource ( renderTargetConstantBuffer, 0, nullptr, &cb, sizeof ( PRMat ) * 2, 0 );

		graphicsContext->immediateContext->VSSetShader ( renderTargetVertexShader, nullptr, 0 );
		graphicsContext->immediateContext->VSSetConstantBuffers ( 0, 1, &renderTargetConstantBuffer );
		graphicsContext->immediateContext->PSSetShader ( renderTargetPixelShader, nullptr, 0 );
		graphicsContext->immediateContext->PSSetShaderResources ( 0, 1, &renderTargetBufferSRV );
		graphicsContext->immediateContext->PSSetSamplers ( 0, 1, &samplerState );

		graphicsContext->immediateContext->IASetVertexBuffers ( 0, 1, &vertexBuffer, &stride, &offset );
		graphicsContext->immediateContext->IASetPrimitiveTopology ( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		graphicsContext->immediateContext->IASetInputLayout ( renderTargetInputLayout );

		graphicsContext->immediateContext->OMSetDepthStencilState ( depthStencilState, 1 );
		graphicsContext->immediateContext->RSSetState ( rasterizerState );

		graphicsContext->immediateContext->Draw ( 6, 0 );

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