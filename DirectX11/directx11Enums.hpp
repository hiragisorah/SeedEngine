#pragma once

enum class ShaderID
{
	Null,
};

enum class RenderTargetID
{
	Null,
	Default,
};

enum class DepthStencilID
{
	Null,
	Default,
};

enum class SamplerID
{
	Null,
};

enum class BlendID
{
	Null,
};

enum class RasterizerID
{
	Null,
	CW,
	CCW,
	WF_CW,
	WF_CCW,
	None,
	WF_None
};

enum class ViewPortID
{
	Null,
	Default,
};

enum class MeshID
{
	Null,
};

enum class TextureID
{
	Null,
};

enum class DescFormat
{
	Null,
	BackBuffer,
	R32F,
	R8G8B8A8UNORM,
	R32G32B32A32F,
};