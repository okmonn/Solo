#pragma once

// 移動方向
enum class DIR {
	non,
	up,
	down,
	right,
	left
};

// キャラの状態
enum class State {
	go,         //前進
	attack1,    //突き
	escape,     //逃亡
	wait,       //待機
	attack2,    //振り
	win,        //勝利
	masicSet,   //詠唱待機
	tool,       //道具
	pinch,      //瀕死
	gurd,       //防御
	skill,      //スキル
	abnormality,//状態異常
	damage,     //ダメージ
	masic,      //魔法
	sleep,      //睡眠
	avoid,      //回避
	item,       //アイテム
	die         //死亡
};

// ステータスの最大数
#define STATE_MAX 18
