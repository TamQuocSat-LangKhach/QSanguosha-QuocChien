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

-- translation for Hegemony Formation Package

return {
	["formation"] = "Trận",
	["formation_equip"] = "Trận",

	["#dengai"] = "Kiểu Nhiên Đích Tráng Sĩ",
	["dengai"] = "Đặng Ngải",
	["tuntian"] = "Đồn Điền",
	[":tuntian"] = "Sau khi bạn mất đi bài ngoài lượt, có thể tiến hành phán xét. Nếu kết quả phán xét không phải là chất Cơ, bạn có thể đặt phán xét này từ chồng bài bỏ lên tướng này, gọi là [Điền]. Với mỗi [Điền], khoảng cách từ bạn tới người khác -1.",
	["@tuntian-gotofield"] = "Đồn Điền: Đặt lá phán xét [%arg] lên tướng thành [Điền]" ,
	["field"] = "Điền",
	["#tuntian-dist"] = "Đồn Điền" ,
	["jixi"] = "Cấp Tập",
	[":jixi"] = "Chủ tướng kỹ, giảm 0.5 máu gốc. Bạn có thể sử dụng [Điền] như [Thuận Thủ Khiên Dương].",
	["ziliang"] = "Tư Lương",
	[":ziliang"] = "Phó tướng kỹ: Sau khi 1 người cùng thế lực nhận sát thương, bạn có thể giao cho họ 1 [Điền].",
	["@ziliang-give"] = "Có thể kích \"Tư Lương\" để giao [Điền] cho người bị thương.",
	["~ziliang"] = "Chọn lá [Điền] rồi bấm \"Xác nhận\".",

	["#caohong"] = "Ngụy Chi Phúc Tướng",
	["caohong"] = "Tào Hồng",
	["huyuan"] = "Hộ Viện",
	[":huyuan"] = "Giai đoạn kết thúc, bạn có thể chọn:\n1. Giao 1 lá không phải trang bị cho 1 người;\n2. Đặt 1 lá trang bị vào vùng trang bị của 1 người; Nếu làm vậy, bạn có thể bỏ 1 lá trong vùng trang bị hoặc phán xét của 1 người.",
	["@huyuan-equip"] = "Có thể phát động \"Hộ Viện\", giao 1 lá phi trang bị cho 1 người hoặc đặt trang bị vào vùng trang bị của 1 người",
	["@huyuan-discard"] = "Hộ Viện: Bỏ 1 lá trên bàn chơi.",
	["heyi"] = "Hạc Dực",
	[":heyi"] = "Trận pháp kỹ: Người cùng đội hình với bạn nhận kỹ năng \"Phi Ảnh\".",
	["HeyiSummon"] = "Hạc Dực",
	["#heyi_feiying"] = "Phi Ảnh",
	["feiying"] = "Phi Ảnh",
	[":feiying"] = "Tỏa định kỹ: Khoảng cách từ người  khác đến bạn +1.",

	["#jiangwei"] = "Long Đích Y Bát",
	["jiangwei"] = "Khương Duy",
	["tiaoxin"] = "Khiêu Hấn",
	[":tiaoxin"] = "Một lần trong giai đoạn hành động, có thể lệnh 1 người có tầm đánh tới bạn sử dụng [Sát] lên bạn, nếu không bạn bỏ 1 lá của người đó.",
	["@tiaoxin-slash"] = "%src đã phát động \"Khiêu Hấn\", hãy sử dụng [Sát] lên %src",
	["yizhi"] = "Di Chí",
	[":yizhi"] = "Phó tướng kỹ - Giảm 0.5 máu gốc: Nếu Chủ tướng của bạn có kỹ năng \"Quan Tinh\" thì số lá bài được xem luôn là 5; nếu không, bạn nhận kỹ năng \"Quan Tinh\".",
	["tianfu"] = "Thiên Phúc",
	[":tianfu"] = "Chủ tướng kỹ, Trận pháp kỹ: Trong lượt của người có nằm trong quan hệ đội hình với người khác, bạn nhận kỹ năng \"Khán Phá\".",
	["TianfuSummon"] = "Thiên Phúc",
	["guanxing_jiangwei"] = "Quan Tinh",

	["#jiangwanfeiyi"] = "Xã Tắc Cổ Quăng",
	["jiangwanfeiyi"] = "Tưởng Uyển & Phí Y",
	["&jiangwanfeiyi"] = "Tưởng Uyển Phí Y",
	["shengxi"] = "Sinh Tức",
	[":shengxi"] = "Giai đoạn kết thúc, nếu trong lượt này bạn không gây sát thương, có thể rút 2 lá bài.",
	["shoucheng"] = "Thủ Thành",
	[":shoucheng"] = "Sau khi người chơi cùng thế lực mất đi lá bài cuối cùng trên tay ngoài lượt, có thể cho họ rút 1 lá bài.",
	["@shoucheng"] = "Có thể phát động \"Thủ Thành\", lệnh cho 1 người rút 1 lá.",

	["#jiangqin"] = "Kỳ Hề Chi Khí",
	["jiangqin"] = "Tưởng Khâm",
	["shangyi"] = "Thượng Nghĩa",
	[":shangyi"] = "Một lần trong giai đoạn hành động, có thể lệnh cho một người chơi khác xem bài trên tay của bạn, sau đó bạn lựa chọn:\n1. Bạn xem bài trên tay họ và bỏ 1 lá màu đen trong đó.\n2. Bạn xem tất cả tướng ẩn của họ.",
	["@shangyi-choose"] = "Lựa chọn xem tướng hoặc bài trên tay của %dest",
	["shangyi:hidden_general"] = "Xem Tướng ẩn",
	["shangyi:handcards"] = "Xem bài trên tay",
	["niaoxiang"] = "Điểu Tường",
	[":niaoxiang"] = "Trận pháp kỹ:\nSau khi bạn xác định từng mục tiêu của [Sát], nếu mục tiêu đó là người bên cạnh bạn và họ không nằm trong quan hệ đội hình với người khác, lệnh mục tiêu cần sử dụng 2 [Thiểm] để triệt tiêu lá [Sát] này.\nNếu bạn là người vây công trong quan hệ vây công, sau khi người vây công xác định từng mục tiêu của lá [Sát], nếu mục tiêu này là người bị vây công, lệnh họ cần sử dụng 2 [Thiểm] để triệt tiêu lá [Sát] này.",
	["NiaoxiangSummon"] = "Điểu Tường",

	["#xusheng"] = "Giang Đông Đích Thiết Bích",
	["xusheng"] = "Từ Thịnh",
	["yicheng"] = "Nghi Thành",
	[":yicheng"] = "Sau khi người cùng đội hình với bạn xác định mục tiêu của [Sát] hoặc trở thành mục tiêu của [Sát], họ có thể rút 1 lá, sau đó bỏ 1 lá.",
    ["@yicheng"] = "Có thể phát động \"Nghi Thành\" của %src, rút 1 và bỏ 1 lá",
    ["#yicheng-formation"] = "Nghi Thành",

	["#yuji"] = "Hồn Nhiễu Tả Hữu",
	["yuji"] = "Vu Cát",
	["qianhuan"] = "Thiên Huyễn",
	[":qianhuan"] = "Sau khi 1 người cùng thế lực nhận sát thương, có thể đem 1 lá bài của bạn đặt lên tướng này, gọi là [Huyễn] (Không được đặt lá trùng chất với lá [Huyễn] đã có). Khi 1 người chơi cùng thế lực trở thành mục tiêu duy nhất của lá cơ bản hoặc công cụ, bạn có thể đưa 1 lá [Huyễn] vào chồng bài bỏ, hủy bỏ mục tiêu này.",
	["@qianhuan-put"] = "Có thể phát động \"Thiên Huyễn\", đặt 1 lá khác chất với các lá [Huyễn] khác." ,
	["sorcery"] = "Huyễn",
	["@qianhuan-cancel"] = "Có thể phát động \"Thiên Huyễn\", hủy bỏ mục tiêu %dest của lá [%arg]",

	["#hetaihou"] = "Lộng Quyền Chi Xà Hạt",
	["hetaihou"] = "Hà Thái Hậu",
	["zhendu"] = "Độc Tửu",
	[":zhendu"] = "Đầu giai đoạn hành động của người chơi khác, có thể bỏ 1 lá bài trên tay, xem như họ sử dụng 1 [Tửu], sau đó bạn gây cho họ 1 sát thương.",
	["@zhendu-discard"] = "Có thể phát động \"Độc Tửu\", bỏ 1 lá trên tay.",
	["qiluan"] = "Thích Loạn",
	[":qiluan"] = "Cuối lượt của 1 người, nếu trong lượt này bạn có giết người, bạn có thể rút 3 lá.",

	["#lord_liubei"] = "Long Hoành Thục Hán",
	["lord_liubei"] = "Lưu Bị - Quân",
	["&lord_liubei"] = "Lưu Bị" ,
	["zhangwu"] = "Chương Vũ",
	["#zhangwu-draw"] = "Chương Vũ (Rút bài)",
	[":zhangwu"] = "Tỏa định kỹ, khi [Phi Long Đoạt Phượng] tiến vào chồng bài bỏ hoặc vùng trang bị của người khác, bạn thu lấy nó; Khi bạn mất đi [Phi Long Đoạt Phượng] không vì sử dụng, bạn mở nó ra, đặt vào đáy chồng bài rút và bạn rút 2 lá.",
	["shouyue"] = "Thụ Việt",
	[":shouyue"] = "Quân chủ kỹ, Tỏa định kỹ, Bạn có \"Ngũ Hổ Tướng Đại Kỳ\".\n\n#\"Ngũ Hổ Tướng Đại Kỳ\"\n" ..
					"Người thuộc thế lực Thục thay đổi các kỹ năng sau:\n" ..
					"Võ Thánh: Có thể sử dụng hoặc đánh ra 1 lá như [Sát].\n" ..
					"Bào Hao: Bổ xung mô tả: Sau khi bạn chỉ định mục tiêu của [Sát], vô hiệu phòng cụ của mục tiêu.\n" ..  --remove the detail of Qinggang-like effect
					"Long Đảm: Bổ xung mô tả: Sau khi sử dụng hoặc đánh ra [Sát] hoặc [Thiểm] bởi phát động \"Long Đảm\", rút 1 lá.\n" ..
					"Liệt Cung: Bổ xung mô tả: Tầm đánh của bạn +1\n" ..
					"Thiết Kỵ: Thay \"1 tướng đã mở\" thành \"tất cả tướng đã mở\"",
	["jizhao"] = "Kích Chiếu",
	[":jizhao"] = "Hạn định kỹ, Khi ban trong trạng thái hấp hối, có thể bổ sung bài trên tay đến giới hạn máu, hồi máu đến 2, mất \"Thụ Việt\" và nhận \"Nhân Đức\"",
	["@jizhao"] = "Kích Chiếu",

	["DragonPhoenix"] = "Phi Long Đoạt Phượng",
	[":DragonPhoenix"] = "Bài Trang bị - Vũ khí\n\nTầm đánh: 2\nKỹ năng:\n" ..
					"1. Sau khi xác định từng mục tiêu của [Sát], có thể lệnh mục tiêu bỏ đi 1 lá của họ.\n" ..
					"2. Khi mục tiêu của [Sát] từ bạn vào trạng thái hấp hối, có thể thu lấy 1 lá trên tay họ.\n" ,
	["@dragonphoenix-discard"] = "Đã phát động [Phi Long Đoạt Phượng], hãy bỏ 1 lá.",

	["DragonPhoenix:revive"] = "Có thể bấm \"Xác nhận\" để chọn 1 tướng cùng thế lực với bạn và lệnh cho họ quay lại trò chơi.",

}
