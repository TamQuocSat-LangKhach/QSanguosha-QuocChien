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

-- translation for StrategicAdvantage Package

return {
	["strategic_advantage"] = "Thế Bị Thiên",

	["transfer"] = "Hợp",
	["is_transferable"] = "Lá này có thể được \"Hợp Tung\"",

	["Blade"] = "Thanh Long Yển Nguyệt Đao",
	[":Blade"] = "Bài Trang bị - Vũ khí\n\nTầm đánh: 3\nKỹ năng: Tỏa định kỹ, Khi sử dụng [Sát], mục tiêu của lá sát không thể lật tướng cho đến khi [Sát] hoàn tất.",

	["Halberd"] = "Phương Thiên Hoạ Kích",
	[":Halberd"] = "Bài Trang bị - Vũ khí\n\nTầm đánh: 4\nKỹ năng: Sau khi chỉ định mục tiêu cho [Sát], có thể chỉ định ở các thế lực khác, mỗi thế lực một người chơi, đồng thời có thể chọn những người chơi chưa lật tướng làm mục tiêu, nhưng nếu có mục tiêu sử dụng [Thiểm] sẽ vô hiệu hoá [Sát] với toàn bộ mục tiêu còn lại.",
	["halberd"] = "Phương Thiên Họa Kích",
	["#HalberdNullified"] = "Do hiệu quả của [%arg], %from dùng [%arg2] với %to vô hiệu",
	["@halberd-use"] = "Sử dụng hiệu ứng của [Phương Thiên Họa Kích]?",

	["Breastplate"] = "Hộ Tâm Kính",
	[":Breastplate"] = "Bài Trang bị - Phòng cụ\n\nKỹ năng: Khi nhận sát thương, nếu sát thương này không nhỏ hơn số máu hiện tại của bạn, có thể bỏ lá này từ vùng trang bị để vô hiệu hoá sát thương đó.",
	["#Breastplate"] = "%from đã vô hiệu hoá %arg điểm sát thương [%arg2] từ %to",

	["IronArmor"] = "Minh Quang Khải",
	[":IronArmor"] = "Bài Trang bị - Phòng cụ\n\nKỹ năng:\n" ..
	"1. Tỏa định kỹ, khi là mục tiêu của [Hỏa Thiêu Liên Doanh], [Hỏa Công] và [Sát Hỏa], hủy bỏ mục tiêu đối với bạn.\n" ..
	"2. Tỏa định kỹ, nếu là tiểu thế lực, không thể rơi vào trạng thái bị xích.\n" ,
	["#IronArmor"] = "%from đã phát động [%arg]",


	["WoodenOx"] = "Mộc Ngưu Lưu Mã",
	[":WoodenOx"] = "Bài Trang bị - Bảo vật\n\nKỹ năng\n" ..
	"1. Một lần Giai đoạn hành động, nếu bạn có ít hơn 5 lá trong [Mộc Ngưu Lưu Mã], có thể đặt 1 lá trên tay vào [Mộc Ngưu Lưu Mã], sau đó có thể chuyển [Mộc Ngưu Lưu Mã] sang vùng trang bị của người chơi khác.\n" ..
	"2. Có thể sử dụng hoặc đánh ra bài trên [Mộc Ngưu Lưu Mã] như bài trên tay.\n" ..
	"3. Khi bạn mất [Mộc Ngưu Lưu Mã], nếu thẻ này không chuyển sang vùng trang bị khác, bỏ toàn bộ bài trên[Mộc Ngưu Lưu Mã].\n" ..
	"* Bản thân luôn có thể xem lại bài trên [Mộc Ngưu Lưu Mã].",
	["@wooden_ox-move"] = "Bạn có thể chuyển  [Mộc Ngưu Lưu Mã] sang vùng trang bị của một người chơi khác",
	["wooden_ox"] = "Mộc Ngưu Lưu Mã",
	["#WoodenOx"] = "%from đánh ra %arg lá %arg2 bài",


	["JadeSeal"] = "Ngọc Tỉ",
	[":JadeSeal"] = "Bài Trang bị - Bảo vật\n\nKỹ năng: Tỏa định kỹ, Nếu đã lật tướng:\n" ..
	"1. Phe của bạn là Đại thế lực duy nhất, tất cả phe khác là Tiểu Thế Lực.\n" ..
	"2. Giai đoạn rút bài, bạn rút thêm 1 lá\n" ..
	"3. Đầu giai đoạn hành động, xem như sử dụng 1 lá [Tri Bỉ Tri Kỉ].\n" ,
	["@JadeSeal"] = "Phát động [Ngọc Tỉ], xem như dùng 1 [Tri Kỷ Tri Bỉ]",
	["~JadeSeal"] = "Chọn mục tiêu [Tri Kỷ Tri Bỉ] rồi bấm \"Xác nhận\"",

	["drowning"] = "Thuỷ Yêm Thất Quân",
	[":drowning"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nLựa chọn: 1 người khác có bài trong vùng trang bị\nMục tiêu: Người đã chọn\nHiệu quả: Mục tiêu lựa chọn bỏ tất cả bài trong vùng trang bị hoặc nhận 1 sát thương Lôi.",
	["drowning:throw"] = "Bỏ tất cả bài trong vùng trang bị",
	["drowning:damage"] = "Nhận 1 sát thương Lôi",

	["burning_camps"] = "Hoả Thiêu Liên Doanh",
	[":burning_camps"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động.\nMục tiêu: Người phía sau bạn và tất cả người cùng đội hình với người này.\nHiệu quả: Bạn gây 1 sát thương Hoả đối với mục tiêu. ",

	["lure_tiger"] = "Điệu Hổ Ly Sơn",
	[":lure_tiger"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nLựa chọn: Từ 1 đến 2 người khác\nMục tiêu: Người đã lựa chọn\nHiệu quả: Mục tiêu không được tính khoảng cách, vị trí, không được sử dụng bài hay được chọn làm mục tiêu của bài, không thể thay đổi số máu cho đến khi hết lượt này.",
	["lure_tiger_effect"] = "Điệu Hổ Ly Sơn",
	["#lure_tiger-prohibit"] = "Điệu Hổ Ly Sơn",

	["fight_together"] = "Lục Lực Đồng Tâm",
	[":fight_together"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nLựa chọn: 1 người thuộc đại thế lực hoặc tiểu thế lực\nMục tiêu: Tất cả người thuộc cùng cấp độ thế lực với người đã chọn.\nHiệu quả: Nếu mục tiêu đang có trạng thái xích, họ rút 1 lá; nếu không, họ nhận trạng thái xích.\nTrọng chú: Có thể đưa lá này vào chồng bài bỏ để rút 1 lá.",
	["@fight_together-choice"] = "Lục Lực Đồng Tâm: Chọn thế lực hoặc đổi bài",
	["fight_together:big"] = "Đại Thế Lực",
	["fight_together:small"] = "Tiểu Thế Lực",

	["alliance_feast"] = "Liên Quân Thịnh Yến",
	[":alliance_feast"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nMục tiêu: bản thân và một thế lực khác phe có người chơi.\nHiệu quả: Bạn được rút số bài và hồi số máu bằng tổng số người hiện tại của phe đó; những người trong phe đó Rút 1 thẻ bài rồi loại bỏ trạng thái xích.",
	["@alliancefeast-choose"] = "Liên Quân Thịnh Yến: Chọn số máu hồi phục, số lượng còn lại dùng để rút bài.",

	["threaten_emperor"] = "Hiệp Thiên Tử Dĩ Lệnh Chư Hầu",
	[":threaten_emperor"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nMục tiêu: Bản thân nếu thuộc phe đại thế lực.\nHiệu quả: Kết thúc lượt hành động. Khi kết thúc giai đoạn bỏ bài, có thể bỏ đi 1 thẻ để nhận thêm một lượt sau lượt này.",
	["@threaten_emperor"] = "Nhận hiệu quả của [Hiệp Thiên Tử Dĩ Lệnh Chư Hầu], có thể bỏ 1 lá trên tay để nhận thêm 1 lượt đi tiếp.",

	["imperial_order"] = "Sắc lệnh",
	[":imperial_order"] = "Bài công cụ\n\nThời điểm: Giai đoạn hành động\nMục tiêu: Tất cả người chơi chưa mở tướng.\nHiệu quả: Mục tiêu chọn 1 mục: 1. Mở 1 tướng và rút 1 lá; 2.Bỏ 1 trang bị; 3. Mất 1 máu.\n\n※Nếu lá này tiến vào chồng bài bỏ không phải do sử dụng, lá này bị loại khỏi trận đấu, sau đó đưa [Chiếu Thư] vào đáy chồng bài rút. Trước khi kết thúc lượt này, tất cả người chơi chưa có thế lực giải quyết hiệu quả của lá này.",

	["#RemoveImperialOrder"] = "[%arg] bị bỏ ra nhưng chưa dùng, sẽ bị loại khỏi trận đấu.",
	["#ImperialOrderEffect"] = "%from kết thúc lượt, phát động hiệu quả của [%arg] đã bị loại bỏ",
	
    ["@imperial_order-choose"] = "[Sắc Lệnh]: Lựa chọn 1 mục:\n1. Mở 1 tướng và rút bài;\n2. Bỏ 1 trang bị;\n3. Mất 1 máu.",
	["imperial_order:show_head"] = "Mở chủ tướng",
	["imperial_order:show_deputy"] = "Mở phó tướng",
    ["imperial_order:dis_equip"] = "Bỏ trang bị",
    ["imperial_order:cancel"] = "Mất 1 máu",
    ["@imperial_order-equip"] = "[Sắc Lệnh]: chọn 1 trang bị để bỏ.",
	
}