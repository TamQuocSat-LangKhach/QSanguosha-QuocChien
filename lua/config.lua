--[[********************************************************************
	Copyright (c) 2013-2015 Mogara

  This file is part of QSanguosha-Hegemony.

  This game is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 3.0
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  See the LICENSE file for more details.

  Mogara
*********************************************************************]]

-- this script to store the basic configuration for game program itself
-- and it is a little different from config.ini

config = {
	kingdoms = { "wei", "qun", "shu", "wu", "careerist", "god" },
	kingdom_colors = {
		wei = "#547998",
		shu = "#D0796C",
		wu = "#4DB873",
		qun = "#8A807A",
		careerist = "#A500CC",
		god = "#96943D",
	},

	skill_colors = {
		compulsory = "#0000FF",
		once_per_turn = "#008000",
		once_per_round = "#008000",
		once_per_whole_turn = "#008000",
		once_per_your_whole_turn = "#008000",
		once_per_whole_game = "#008000",
		twice_per_turn = "#008000",
		twice_per_whole_turn = "#008000",
		three_per_your_whole_turn = "#008000",
		four_per_turn = "#008000",
		four_per_your_whole_turn = "#008000",
		x_per_whole_turn = "#008000",
		limited = "#FF0000",
		head = "#00FF00",
		deputy = "#00FFFF",
		array = "#800080",
		lord = "#FFA500",
		switch = "#FFC0CB",
	},

	-- Sci-fi style background
	--dialog_background_color = "#49C9F0";
	--dialog_background_alpha = 75;
	dialog_background_color = "#D6E7DB";
	dialog_background_alpha = 255;

	package_names = {
		"StandardCard",
		"StrategicAdvantage",
		"FormationEquip",
		"MomentumEquip",
		"TransformationEquip",
		"PowerEquip",
		"LordEXCard",
		"LangKhachCard",
		"Joy",
		"Disaster",

		"Standard",
		"Formation",
		"Momentum",
		"Transformation",
		"Power",
		"Manoeuvre",
		"NewSGS",
		"MOL",
		"LordEX",
		"Overseas",
		"Xiliang",
		"Removed",
		"LangKhach",
		"Moesen",
		"Test",
		"JiangeDefense"
	},

	easy_text = {
		"Chậm quá, ngồi chờ nãy giờ !",
		"Nhanh lên dùm đi, ta đội ơn !",
		"Hay, đánh rất hay !",
		"Hảo thủ đoạn, thật không thể xem thường nha~",
		"Hả, đồ cải trắng. Làm lục bình còn muốn vươn cao ?",
		"Ngươi đừng nên đùa giỡn nha ~",
		"Nè, giống nhau cả mà, ta không ra tay đâu.",
		"A, bài tốt thì chỉ đến như vậy thôi !",
		"Sát! Gặp thần sát thần ! Gặp phật sát phật !",
		"Ngươi nghĩ vậy quá xấu rồi ha ?!"
	},

	robot_names = {
		"Tài Tống",
		"#S",
		"Lãng Khách",
		"Huấn Hoa Hồng",
		"Đầu cắt moi",
		"Quan Vũ",
		"Ong Thành Đạt",
		"Đường Tank",
		"Ultimate AI",
		"KayaK",
		"Ricky Dương",
		"Yugi Muto",
		"Ya Boy Khổng Minh"
	},
}
