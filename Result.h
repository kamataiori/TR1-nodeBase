#pragma once
#include "imnodes.h"
#include "imgui.h"
#include <vector>
#include "struct.h"


class Result
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(char* keys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void DrawNodeEditor();


	float aaa{};

	Line line;

	SplitLine splitLine;

	Particle particle;

	BackGround backGround;

	PaBackGround pabackGround;

	Box box;


	// 保存されたリンクを描画
	std::vector<std::pair<int, int>> links;


	float e{};
	float ViscosityCoefficient{};
	float fx{};
	float fy{};

	bool particleStart{};

	const int particleWidthRange = 640;
	const int particleHieghtRange = 720;


};

