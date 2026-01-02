#pragma once

	enum class gameMode {
		oneVillage,
		twoVillages
	};
	struct gameConfig {
		gameMode mode = gameMode::oneVillage;
	};


