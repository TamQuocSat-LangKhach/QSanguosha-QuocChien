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
	[":tuntian"] = "\n• Sau khi bạn mất đi bài ngoài lượt, bạn có thể tiến hành phán xét; nếu kết quả phán xét không phải là chất CƠ, bạn có thể đặt kết quả phán xét này từ chồng bài bỏ lên tướng này, gọi là [Điền].\n• Khoảng cách từ bạn tới người khác -X (X là số [Điền] bạn có).",
	["@tuntian-gotofield"] = "Đồn Điền: Đặt lá phán xét [%arg] lên tướng thành [Điền]" ,
	["field"] = "Điền",
	["#tuntian-dist"] = "Đồn Điền" ,
	["jixi"] = "Cấp Tập",
	[":jixi"] = "Chủ tướng kỹ, Giảm 0.5 máu gốc: Bạn có thể chuyển hóa sử dụng [Điền] thành [Thuận Thủ Khiên Dương].",
	["ziliang"] = "Tư Lương",
	[":ziliang"] = "Phó tướng kỹ: Sau khi 1 người cùng thế lực nhận sát thương, bạn có thể giao cho họ 1 [Điền].",
	["@ziliang-give"] = "Có thể kích »Tư Lương« để giao [Điền] cho người bị thương.",
	["~ziliang"] = "Chọn lá [Điền] rồi bấm \"Xác nhận\".",

	["#caohong"] = "Ngụy Chi Phúc Tướng",
	["caohong"] = "Tào Hồng",
	["huyuan"] = "Hộ Viện",
	[":huyuan"] = "Khi bắt đầu giai đoạn kết thúc, bạn có thể chọn 1 mục:\n1. Giao 1 lá không phải trang bị cho 1 người;\n2. Đặt 1 lá trang bị vào vùng trang bị của 1 người; Nếu làm vậy, bạn có thể bỏ 1 lá trong vùng trang bị hoặc phán xét của 1 người.",
	["@huyuan-equip"] = "Có thể phát động »Hộ Viện«, giao 1 lá phi trang bị cho 1 người hoặc đặt trang bị vào vùng trang bị của 1 người",
	["@huyuan-discard"] = "Hộ Viện: Bỏ 1 lá trên bàn chơi.",
	["heyi"] = "Hạc Dực",
	[":heyi"] = "Trận pháp kỹ: Quan hệ đội hình: Nếu bạn có nằm trong quan hệ đội hình, người cùng đội hình với bạn nhận kỹ năng »Phi Ảnh«.",
	["HeyiSummon"] = "Hạc Dực",
	["#heyi_feiying"] = "Phi Ảnh",
	["feiying"] = "Phi Ảnh",
	[":feiying"] = "Tỏa định kỹ: Khoảng cách từ người khác đến bạn +1.",

	["#jiangwei"] = "Long Đích Y Bát",
	["jiangwei"] = "Khương Duy",
	["tiaoxin"] = "Khiêu Hấn",
	[":tiaoxin"] = "Một lần trong giai đoạn ra bài, bạn có thể lệnh 1 người có tầm đánh tới bạn sử dụng [Sát] lên bạn, nếu không, bạn bỏ 1 lá của họ.",
	["@tiaoxin-slash"] = "%src đã phát động »Khiêu Hấn«, hãy sử dụng [Sát] lên %src",
	["yizhi"] = "Di Chí",
	[":yizhi"] = "Phó tướng kỹ, Giảm 0.5 máu gốc: Nếu Chủ tướng của bạn có kỹ năng »Quan Tinh«, số lá được xem luôn là 5; nếu không, bạn nhận kỹ năng »Quan Tinh«.",
	["tianfu"] = "Thiên Phúc",
	[":tianfu"] = "Chủ tướng kỹ, Trận pháp kỹ: Quan hệ đội hình: Trong lượt của người có nằm trong quan hệ đội hình với người khác, bạn nhận kỹ năng »Khán Phá«.",
	["TianfuSummon"] = "Thiên Phúc",
	["guanxing_jiangwei"] = "Quan Tinh",

	["#jiangwanfeiyi"] = "Xã Tắc Cổ Quăng",
	["jiangwanfeiyi"] = "Tưởng Uyển & Phí Y",
	["&jiangwanfeiyi"] = "Tưởng Uyển Phí Y",
	["shengxi"] = "Sinh Tức",
	[":shengxi"] = "Khi bắt đầu giai đoạn kết thúc, nếu trong lượt này bạn không gây sát thương, bạn có thể rút 2 lá.",
	["shoucheng"] = "Thủ Thành",
	[":shoucheng"] = "Sau khi người chơi cùng thế lực mất đi lá cuối cùng trên tay họ nếu ở ngoài lượt của họ, bạn có thể lệnh họ rút 1 lá.",
	["@shoucheng"] = "Có thể phát động »Thủ Thành«, lệnh cho 1 người rút 1 lá.",

	["#jiangqin"] = "Kỳ Hề Chi Khí",
	["jiangqin"] = "Tưởng Khâm",
	["shangyi"] = "Thượng Nghĩa",
	[":shangyi"] = "Một lần trong giai đoạn ra bài, bạn có thể lệnh cho 1 người khác xem bài trên tay của bạn, sau đó bạn lựa chọn 1 mục:\n1. Bạn xem bài trên tay họ và bỏ 1 lá màu đen trong đó.\n2. Bạn xem tất cả tướng ẩn của họ.",
	["@shangyi-choose"] = "Lựa chọn xem tướng hoặc bài trên tay của %dest",
	["shangyi:hidden_general"] = "Xem Tướng ẩn",
	["shangyi:handcards"] = "Xem bài trên tay",
	["niaoxiang"] = "Điểu Tường",
	[":niaoxiang"] = "Trận pháp kỹ: Quan hệ vây công:\n• Sau khi bạn xác định mục tiêu của [Sát], ứng với mỗi mục tiêu, nếu mục tiêu đó là người bên cạnh bạn và họ không nằm trong quan hệ đội hình với người khác, lệnh họ cần sử dụng 2 [Thiểm] để triệt tiêu lá [Sát] này.\n• Nếu bạn là người vây công, sau khi người vây công xác định mục tiêu của lá [Sát], ứng với mỗi mục tiêu, nếu mục tiêu này là người bị vây công, lệnh họ cần sử dụng 2 [Thiểm] để triệt tiêu lá [Sát] này.",
	["NiaoxiangSummon"] = "Điểu Tường",

	["#xusheng"] = "Giang Đông Đích Thiết Bích",
	["xusheng"] = "Từ Thịnh",
	["yicheng"] = "Nghi Thành",
	[":yicheng"] = "Sau khi người cùng đội hình với bạn xác định mục tiêu của [Sát] hoặc trở thành mục tiêu của [Sát], họ có thể rút 1 lá, sau đó bỏ 1 lá.",
    ["@yicheng"] = "Có thể phát động »Nghi Thành« của %src, rút 1 và bỏ 1 lá",
    ["#yicheng-formation"] = "Nghi Thành",

	["#yuji"] = "Hồn Nhiễu Tả Hữu",
	["yuji"] = "Vu Cát",
	["qianhuan"] = "Thiên Huyễn",
	[":qianhuan"] = "\n• Sau khi 1 người cùng thế lực nhận sát thương, có thể đem 1 lá bài của bạn đặt lên tướng này, gọi là [Huyễn] (Không thể đặt lá trùng chất với những [Huyễn] đã có).\n• Khi 1 người chơi cùng thế lực trở thành mục tiêu duy nhất của lá cơ bản hoặc công cụ, bạn có thể đưa 1 [Huyễn] vào chồng bài bỏ, hủy bỏ mục tiêu này.",
	["@qianhuan-put"] = "Có thể phát động »Thiên Huyễn«, đặt 1 lá khác chất với các lá [Huyễn] khác." ,
	["sorcery"] = "Huyễn",
	["@qianhuan-cancel"] = "Có thể phát động »Thiên Huyễn«, hủy bỏ mục tiêu %dest của lá [%arg]",

	["#hetaihou"] = "Lộng Quyền Chi Xà Hạt",
	["hetaihou"] = "Hà Thái Hậu",
	["zhendu"] = "Độc Tửu",
	[":zhendu"] = "Khi bắt đầu giai đoạn ra bài của người chơi khác, bạn có thể bỏ 1 lá bài trên tay; sau đó, nếu họ có thể sử dụng tửu:\n- Họ xem như sử dụng 1 [Tửu];\n- Bạn gây 1 sát thương cho họ.",
	["@zhendu-discard"] = "Có thể phát động »Độc Tửu«, bỏ 1 lá trên tay.",
	["qiluan"] = "Thích Loạn",
	[":qiluan"] = "Khi kết thúc lượt của 1 người, nếu trong lượt này bạn đã giết người, bạn có thể rút 3 lá.",

	["#lord_liubei"] = "Long Hoành Thục Hán",
	["lord_liubei"] = "Lưu Bị - Quân",
	["&lord_liubei"] = "Lưu Bị" ,
	["zhangwu"] = "Chương Vũ",
	["#zhangwu-draw"] = "Chương Vũ (Rút bài)",
	[":zhangwu"] = "Tỏa định kỹ:\n• Khi [Phi Long Đoạt Phượng] tiến vào chồng bài bỏ hoặc vùng trang bị của người khác, bạn thu lấy nó.\n• Khi bạn mất đi [Phi Long Đoạt Phượng] không vì sử dụng, bạn mở nó ra, đặt vào đáy chồng bài rút và bạn rút 2 lá.",
	["shouyue"] = "Thụ Việt",
	[":shouyue"] = "Quân chủ kỹ, Tỏa định kỹ: Bạn có »Ngũ Hổ Tướng Đại Kỳ«.\n\n»<b>Ngũ Hổ Tướng Đại Kỳ</b>«:" ..
					"\nNgười thuộc thế lực Thục thay đổi các kỹ năng sau:" ..
					"\n- »Võ Thánh«: Thay đổi kỹ năng thành: Bạn có thể chuyển hóa sử dụng/đánh ra 1 lá của bạn thành [Sát]." ..
					"\n- »Bào Hao«: Bổ sung mô tả: Sau khi bạn xác định mục tiêu của [Sát], vô hiệu phòng cụ của mục tiêu." .. 
					"\n- »Long Đảm«: Bổ sung mô tả: Sau khi sử dụng hoặc đánh ra [Sát] hoặc [Thiểm] bởi phát động »Long Đảm«, bạn rút 1 lá." ..
					"\n- »Liệt Cung«: Bổ sung mô tả: Tầm đánh của bạn +1." ..
					"\n- »Thiết Kỵ«: Thay đổi mô tả: \"1 tướng đã mở\" sửa thành \"tất cả tướng đã mở\".",
	["jizhao"] = "Kích Chiếu",
	[":jizhao"] = "Hạn định kỹ: Khi ban trong trạng thái hấp hối, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Bạn bổ sung bài trên tay đến giới hạn máu;\n- Bạn hồi máu đến 2;\n- Bạn mất kỹ năng »Thụ Việt« và nhận kỹ năng »Nhân Đức«.",
	["@jizhao"] = "Kích Chiếu",

	["DragonPhoenix"] = "Phi Long Đoạt Phượng",
	[":DragonPhoenix"] = "Bài Trang bị - Vũ khí\n\nTầm đánh: 2\nKỹ năng:\n" ..
					"1. Sau khi xác định từng mục tiêu của [Sát], có thể lệnh mục tiêu bỏ đi 1 lá của họ.\n" ..
					"2. Khi mục tiêu của [Sát] từ bạn vào trạng thái hấp hối, có thể thu lấy 1 lá trên tay họ.\n" ,
	["@dragonphoenix-discard"] = "Đã phát động [Phi Long Đoạt Phượng], hãy bỏ 1 lá.",

	["DragonPhoenix:revive"] = "Có thể bấm \"Xác nhận\" để chọn 1 tướng cùng thế lực với bạn và lệnh cho họ quay lại trò chơi.",

}
