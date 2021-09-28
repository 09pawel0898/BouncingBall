#pragma once

namespace En
{
	const std::vector<float> spriteVertices = { -0.5f, -0.5f, 0.0f, 0.0f,
												 0.5f, -0.5f, 1.0f, 0.0f,
												 0.5f,  0.5f, 1.0f, 1.0f,
												-0.5f,  0.5f, 0.0f, 1.0f };

	const std::vector<uint16_t> spriteIndices = {  0,1,2,
											 2,3,0 };


	struct SpriteRendererData
	{
	public:
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> vertexArray;
		std::unique_ptr<IndexBuffer<uint16_t>> indexBuffer;
	private:
		VertexBuffer VB;
		VertexBufferLayout VBL;

		

	public:
		SpriteRendererData()
			:	shader(std::make_unique<Shader>("res/shaders/sprite.glsl")),
				vertexArray(std::make_unique<VertexArray>()),
				indexBuffer(std::make_unique<IndexBuffer<uint16_t>>(spriteIndices)),
				VB(spriteVertices, 4 * 4 * sizeof(float)),
				VBL()
		{
			VBL.Push<float>(2);
			VBL.Push<float>(2);
			vertexArray->AddBuffer(VB, VBL);
		}
	};
}