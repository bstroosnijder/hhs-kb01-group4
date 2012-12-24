#ifndef TEXTUREDVECTOR3_H_
#define TEXTUREDVECTOR3_H_
// Our custom FVF, which describes our custom vertex structure
#define D3DFVFTexturedVector3 (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

namespace engine
{
	/**
	 * Struct for vertices with a textures, color and xyz values
	 */
	struct TexturedVector3
	{
		float x;
		float y;
		float z;

		unsigned long color;

		float u;
		float v;
	};
}

#endif