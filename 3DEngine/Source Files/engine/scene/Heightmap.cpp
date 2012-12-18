#include "..\..\..\Header Files\engine\scene\Heightmap.h"

namespace engine
{
	void Heightmap::Init(Renderer* argPRenderer)
	{
		DirectX9Renderer* renderer = (DirectX9Renderer*)argPRenderer;

		// Initialize three vertices for rendering a triangle
		CUSTOMVERTEX g_Vertices[] =
		{

			// Top Face (5-6-1-2)
			{ -1.0f, 0.0f, 1.0f, 0xFF0000FF },
			{ 1.0f, 0.0f, 1.0f, 0xFFAFAFFF },
			{ -1.0f, 0.0f, -1.0f, 0xFFAFAFFF },
			{ 1.0f, 0.0f, -1.0f, 0xFF0000FF },

			
		};

		if( FAILED( renderer->GetDevice()->CreateVertexBuffer( 32 * sizeof( CUSTOMVERTEX ),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
		{
			return;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if( FAILED( g_pVB->Lock( 0, sizeof( g_Vertices ), ( void** )&pVertices, 0 ) ) )
			return;

		memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
		g_pVB->Unlock();
	}

	void Heightmap::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* renderer = (DirectX9Renderer*)argPRenderer;

		D3DXMATRIXA16 matWorld;

    // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
    // every 1000 ms. To avoid the loss of precision inherent in very high 
    // floating point numbers, the system time is modulated by the rotation 
    // period before conversion to a radian angle.
    UINT iTime = timeGetTime() % 1000;
    FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 1000.0f;
    D3DXMatrixRotationY( &matWorld, 0 );
    renderer->GetDevice()->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
	

    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    renderer->GetDevice()->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    renderer->GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );

		renderer->GetDevice()->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
        renderer->GetDevice()->SetFVF( D3DFVF_CUSTOMVERTEX );

		for (int i = 0; i < 6; i++)
			renderer->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}