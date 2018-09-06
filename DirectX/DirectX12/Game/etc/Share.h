#pragma once

// レーンタイプ
enum LaneType {
	TYPE_A,
	TYPE_B,
	TYPE_C,
	TYPE_D,
	TYPE_MAX
};

// ノーツ情報
struct Notes {
	//レーンタイプ
	LaneType type;
	//開始フレーム
	int start;
	//時間
	int time;
};
