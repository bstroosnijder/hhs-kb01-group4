#ifndef RENDERER_H_
#define RENDERER_H_

#include "..\logger\Logger.h"
#include "..\window\Window.h"

namespace engine
{
	/**
	 * The interface renderer serves as an abstraction for the different video driver API's.
	 */
	class Renderer
	{
	public:
		static const unsigned int DIRECTX_9;
		static const unsigned int OPEN_GL;
		
		virtual void* GetDevice()=0;
		virtual void SetupMatricis()=0;

		virtual bool CreateVertexBuffer(void* argPVertexBuffer, unsigned long argSize, unsigned long argStruct, void* argPVertices)=0;
		virtual bool CreateIndexBuffer(void* argPIndexBuffer, unsigned long argSize, short* argPIndices)=0;

		virtual void* GetWorldTop()=0;
		virtual void LoadWorldMatrix(void* argPMatrix)=0;
		virtual void AddToWorldMatrix(void* argPMatrix)=0;

		virtual void TransformWorldMatrix()=0;
		virtual void TransformViewMatrix()=0;
		virtual void TransformProjectionMatrix()=0;

		virtual void SetLight(unsigned long argLightIndex, void* argPLight)=0;
		virtual void LightEnable(unsigned long argLightIndex, bool argEnable)=0;

		virtual void Clear()=0;
		virtual void BeginScene()=0;
		virtual void Push()=0;

		virtual void SetStreamSource(void* argPVertexBuffer, unsigned long argSizePerVertex)=0;
		virtual void SetFVF(unsigned long argStruct)=0;
		virtual void SetIndices(void* argPIndexBuffer)=0;

		virtual void SetMaterial(void* argPMaterial)=0;
		virtual void SetTexture(unsigned long argIndex, void* argPTexture)=0;

		virtual void DrawPrimitive(unsigned long argPrimitiveType, unsigned long argNumPrimitives)=0;
		virtual void DrawIndexedPrimitive(unsigned long argPrimitiveType, unsigned long argNumVertices, unsigned long argNumPrimitives)=0;

		virtual void Pop()=0;
		virtual void EndScene()=0;
		virtual void Present(Window* argWindow)=0;
	};
}

#endif