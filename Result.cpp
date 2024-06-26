#include "Result.h"
//#include <vector>
#include <iostream> // for std::cout
#include <Novice.h>

void Result::Initialize()
{

	aaa = 0.0f;

	line = {
		{ 0.0f,600.0f },
		{ 641.0f,600.0f },
		WHITE,
	};

	splitLine = {
		{641.0f,0.0f},
		{641.0f,720.0f},
		WHITE,
	};

	particle = {

		{0.0f,0.0f},
		{0.0f,0.98f},
		{false},
		{rand() % 3 + 1}
	};
	for (int i = 0; i < 500; i++)
	{
		particle.pos[i].x = 0.0f;
		particle.pos[i].y = 0.0f;
		particle.acceleration[i].x = 0.0f;
		particle.acceleration[i].y = 0.98f;
		particle.isShot[i] = false;
		particle.radius[i] = rand() % 8 + 5;
	}

	backGround =
	{
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},

		{960.0f,360.0f},

		{720.0f},
		{640.0f},
	};

	pabackGround =
	{
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},

		{320.0f,360.0f},

		{720.0f},
		{640.0f},
	};

	box =
	{
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},

		{320.0f,50.0f},

		{40.0f},

		{100.0f},
	};

	e = 0.4f;
	ViscosityCoefficient = 0.1f;
	for (int i = 0; i < 500; i++)
	{
		fx = -ViscosityCoefficient * particle.acceleration[i].x;
		fy = -ViscosityCoefficient * particle.acceleration[i].y;
	}

	particleStart = false;
}

void Result::Update(char* keys)
{
	/*ImGui::Begin("nodes");
	ImGui::End();*/

	DrawNodeEditor();

	box.leftTop.x = box.center.x - box.widelength / 2;
	box.leftTop.y = box.center.y - box.heghtlength / 2;


	if (keys[DIK_D])
	{
		box.widelength++;
	}

	if (keys[DIK_A])
	{
		box.widelength--;
	}

	if (keys[DIK_W])
	{
		box.heghtlength++;
	}

	if (keys[DIK_S])
	{
		box.heghtlength--;
	}

	if (box.heghtlength <= 5)
	{
		box.heghtlength = 5;
	}

	if (box.widelength <= 5)
	{
		box.widelength = 5;
	}

	if (box.widelength >= particleWidthRange)
	{
		box.widelength = (float)particleWidthRange;
	}

	if (box.leftTop.x <= 0)
	{
		box.leftTop.x = 5;
	}

	if (particleStart == false)
	{
		for (int i = 0; i < 500; i++)
		{
			particle.pos[i].x = box.center.x + rand() % (int)box.widelength - (int)box.widelength / 2;
			particle.pos[i].y = box.center.y + rand() % (int)box.heghtlength - (int)box.heghtlength / 2;
			particle.acceleration[i].x = 0.0f;
			particle.acceleration[i].y = 0.0f;
			fx = 0.0f;
			fy = 0.0f;
		}

		if (keys[DIK_SPACE])
		{
			particleStart = true;
		}
	}


	if (particleStart == true)
	{

		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == false)
			{
				particle.isShot[i] = true;
				particle.pos[i].x = box.center.x + rand() % (int)box.widelength - (int)box.widelength / 2;
				particle.pos[i].y = box.center.y + rand() % (int)box.heghtlength - (int)box.heghtlength / 2;
				particle.acceleration[i].y = 0.98f;
				break;
			}

		}

		for (int i = 0; i < 500; i++)
		{
			particle.acceleration[i].x += fx;
			particle.acceleration[i].y += fy;
		}

		//パーティクルを移動させる
		for (int i = 0; i < 500; i++)
		{
			particle.pos[i].y += particle.acceleration[i].y;
			particle.pos[i].x += particle.acceleration[i].x;
		}

		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == true)
			{
				particle.acceleration[i].y += 0.4f;
			}
		}

		for (int i = 0; i < 500; i++)
		{
			if (particle.pos[i].y >= line.Start.y - 8)
			{
				// 50%の確率でプラス方向に、残りの50%の確率でマイナス方向に動く
				particle.acceleration[i].x = 4.98f * ((rand() % 2) * 2 - 1);
				particle.acceleration[i].y = -particle.acceleration[i].y * e;
			}

			if (particle.pos[i].x >= splitLine.Start.x - 8)
			{
				particle.acceleration[i].x = -particle.acceleration[i].x * e;
			}
		}

	}

	if (particleStart == true)
	{
		if (keys[DIK_RETURN])
		{
			particleStart = false;
		}
	}


}

void Result::Draw()
{

	Novice::DrawBox((int)pabackGround.center.x - 320, (int)pabackGround.center.y - 360, (int)pabackGround.widelength, (int)pabackGround.heghtlength, 0.0f, BLACK, kFillModeSolid);


	Novice::DrawBox((int)box.leftTop.x, (int)box.leftTop.y, (int)box.widelength, (int)box.heghtlength, 0.0f, WHITE, kFillModeWireFrame);

	Novice::DrawLine((int)line.Start.x, (int)line.Start.y, (int)line.End.x, (int)line.End.y, line.color);

	Novice::DrawLine((int)splitLine.Start.x, (int)splitLine.Start.y, (int)splitLine.End.x, (int)splitLine.End.y, splitLine.color);

	if (particleStart == true)
	{
		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == true)
			{
				Novice::DrawEllipse((int)particle.pos[i].x, (int)particle.pos[i].y, particle.radius[i], particle.radius[i], 0.0f, BLUE, kFillModeSolid);

			}

		}
	}

	Novice::DrawBox((int)backGround.center.x - 320, (int)backGround.center.y - 360, (int)backGround.widelength, (int)backGround.heghtlength, 0.0f,GRAY, kFillModeSolid);

}

void Result::DrawNodeEditor()
{
	// std::vector<std::pair<int, int>> links;
	int node_hovered = -1;
	std::vector<int> selected_nodes;

	ImGui::Begin("node");

	// ノードIDおよびピンIDの定義
	int node_id = 1;       // 任意の一意のノードID
	int input_pin_id = 2;  // 任意の一意の入力ピンID
	int output_pin_id = 3; // 任意の一意の出力ピンID

	int node_id2 = 4;       // 二つ目のノードID
	int input_pin_id2 = 5;  // 二つ目の入力ピンID
	int output_pin_id2 = 6; // 二つ目の出力ピンID

	int node_id3 = 7;       // 三つ目のノードID
	int input_pin_id3 = 8;  // 三つ目の入力ピンID
	int output_pin_id3 = 9; // 三つ目の出力ピンID

	ImNodes::BeginNodeEditor();

	// ノードのタイトルバーの色を設定
	ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(11, 109, 191, 255));
	ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(81, 148, 204, 255));

	// ノードを開始
	ImNodes::BeginNode(node_id);

	// ノードのタイトルバー
	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("Flag");
	ImNodes::EndNodeTitleBar();

	// 入力ピン
	ImNodes::BeginInputAttribute(input_pin_id);
	ImGui::Text("Input");
	ImNodes::EndInputAttribute();

	// ImGuiで変更したいもの
	ImGui::Checkbox("particleStart", &particleStart);

	// 出力ピン
	ImNodes::BeginOutputAttribute(output_pin_id);
	ImGui::Text("OutPut");
	ImNodes::EndOutputAttribute();

	// ノードを終了
	ImNodes::EndNode();


	// ノードのタイトルバーの色を設定
	ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(40, 19, 101, 205));
	ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(10, 125, 100, 100));


	// 二つ目のノードを開始
	ImNodes::BeginNode(node_id2);

	// ノードのタイトルバー
	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("acceleration");
	ImNodes::EndNodeTitleBar();

	// 入力ピン
	ImNodes::BeginInputAttribute(input_pin_id2);
	ImGui::Text("Input");
	ImNodes::EndInputAttribute();

	// ImGuiで変更したいもの
	ImGui::DragFloat("acceleration.x", &particle.acceleration->x);
	ImGui::DragFloat("acceleration.y", &particle.acceleration->y);

	// 出力ピン
	ImNodes::BeginOutputAttribute(output_pin_id2);
	ImGui::Text("Output");
	ImNodes::EndOutputAttribute();


	// 二つ目のノードを終了
	ImNodes::EndNode();


	// ノードのタイトルバーの色を設定
	ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(4000, 1900, 10100, 2050));
	ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(100, 1025, 1000, 1000));

	// 三つ目のノードを開始
	ImNodes::BeginNode(node_id3);

	// ノードのタイトルバー
	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted("coefficient of restitution");
	ImNodes::EndNodeTitleBar();

	// 入力ピン
	ImNodes::BeginInputAttribute(input_pin_id3);
	ImGui::Text("Input nodemerge");
	ImNodes::EndInputAttribute();

	// ImGuiで変更したいもの
	ImGui::DragFloat("e", &e);

	// 出力ピン
	ImNodes::BeginOutputAttribute(output_pin_id3);
	ImGui::Text("Output nodemerge");
	ImNodes::EndOutputAttribute();


	// 三つ目のノードを終了
	ImNodes::EndNode();


	// ノードエディタのレンダリング中にミニマップを表示
	//ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);

	// ノードのタイトルバーの色を元に戻す
	ImNodes::PopColorStyle();
	ImNodes::PopColorStyle();


	//// 保存されたリンクを描画
	for (int i = 0; i < links.size(); ++i)
	{
		const std::pair<int, int> p = links[i];
		// in this case, we just use the array index of the link
		// as the unique identifier
		ImNodes::Link(i, p.first, p.second);
	}


	ImNodes::EndNodeEditor();


	// 新しいリンクが作成されたかどうかを確認
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
	{
		links.push_back(std::make_pair(start_attr, end_attr));
	}

	// ノードがホバーされているかどうかを確認
	int hovered_node_id;
	if (ImNodes::IsNodeHovered(&hovered_node_id))
	{
		node_hovered = hovered_node_id;
		std::cout << "Node hovered: " << node_hovered << std::endl;
	}

	// 選択されたノードを取得
	const int num_selected_nodes = ImNodes::NumSelectedNodes();
	if (num_selected_nodes > 0)
	{
		selected_nodes.resize(num_selected_nodes);
		ImNodes::GetSelectedNodes(selected_nodes.data());
		for (int node_idd : selected_nodes)
		{
			std::cout << "Node selected: " << node_idd << std::endl;
		}
	}

	ImGui::End();
}
