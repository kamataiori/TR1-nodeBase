#include "Result.h"
//#include <vector>
#include <iostream> // for std::cout

void Result::Initialize()
{
    aaa = 0.0f;
}

void Result::Update()
{
	/*ImGui::Begin("nodes");
	ImGui::End();*/

    DrawNodeEditor();

   
}

void Result::Draw()
{

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

    ImNodes::BeginNodeEditor();

    // ノードのタイトルバーの色を設定
    ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(11, 109, 191, 255));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(81, 148, 204, 255));

    // ノードを開始
    ImNodes::BeginNode(node_id);

    // ノードのタイトルバー
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("nodeTitle");
    ImNodes::EndNodeTitleBar();

    // 入力ピン
    ImNodes::BeginInputAttribute(input_pin_id);
    ImGui::Text("Input node");
    ImNodes::EndInputAttribute();

    // 出力ピン
    ImNodes::BeginOutputAttribute(output_pin_id);
    ImGui::Text("OutPut node");
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
    ImGui::TextUnformatted("nodeBase");
    ImNodes::EndNodeTitleBar();

    // 入力ピン
    ImNodes::BeginInputAttribute(input_pin_id2);
    ImGui::Text("Input nodeBase");
    ImGui::SliderFloat("aaa", &aaa,-10.0f,10.0f);
    ImNodes::EndInputAttribute();

    // 出力ピン
    ImNodes::BeginOutputAttribute(output_pin_id2);
    ImGui::Text("Output nodeBase");
    ImNodes::EndOutputAttribute();


    // 二つ目のノードを終了
    ImNodes::EndNode();

    // ノードエディタのレンダリング中にミニマップを表示
    ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);

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
