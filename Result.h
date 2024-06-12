#pragma once
#include "imnodes.h"
#include "imgui.h"
#include <vector>


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
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void DrawNodeEditor();


	float aaa{};


	// 保存されたリンクを描画
	std::vector<std::pair<int, int>> links;

};

