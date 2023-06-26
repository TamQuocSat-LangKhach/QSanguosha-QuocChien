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

-- translation for Standard General Package

return {
	-- 蜀势力
	["#liubei"] = "Loạn Thế Đích Kiêu Hùng",
	["liubei"] = "Lưu Bị",
	["rende"] = "Nhân Đức",
	[":rende"] = "Giai đoạn hành động，bạn có thể đem tùy ý lượng bài trên tay giao cho 1 người khác chưa nhận bài từ kỹ năng này trong giai đoạn này. Nếu vậy, khi lần đầu tổng số lá bài bạn giao bằng kỹ năng này trong giai đoạn này bằng 2 hoặc nhiều hơn, có thể xem như sử dụng 1 lá cơ bản.",
    ["@rende-basic"] = "Nhân Đức: Chọn lá cơ bản để sử dụng",
    ["rende_basic"] = "Nhân Đức",
	
	["#guanyu"] = "Mĩ Nhiêm Công",
	["guanyu"] = "Quan Vũ",
	["wusheng"] = "Võ Thánh",
	[":wusheng"] = "Có thể sử dụng hoặc đánh ra 1 lá Đỏ như [Sát]. Lá [Sát] Rô bạn sử dụng không hạn chế khoảng cách.",

	["#zhangfei"] = "Vạn Phu Bất Đương",
	["zhangfei"] = "Trương Phi",
	["paoxiao"] = "Bào Hao",
	[":paoxiao"] = "Tỏa định kỹ, Có thể sử dụng lá [Sát] không giới hạn số lượng. Khi bạn sử dụng lá [Sát] thứ 2 trong 1 lượt, rút 1 lá.",
	["#PaoxiaoDraw"] = "%from đã phát động \"%arg\", rút 1 lá",
    ["#PaoxiaoTarget"] = "%from đã phát động \"%arg\", bỏ qua phòng cụ của %to",

	["#zhugeliang"] = "Trì Mộ Đích Thừa Tướng",
	["zhugeliang"] = "Gia Cát Lượng",
	["guanxing"] = "Quan Tinh",
	[":guanxing"] = "Giai đoạn chuẩn bị, bạn có thể xem X lá bài trên đầu chồng bài (X là số người chơi trên bàn, tối đa 5), sau đó sắp xếp tùy ý những lá này lên đầu hoặc đáy chồng bài",
	["kongcheng"] = "Không Thành",
	[":kongcheng"] = "Tỏa định kỹ, Nếu bạn không có bài trên tay\n1. Khi bạn là mục tiêu của lá [Sát] hoặc [Quyết Đấu], hủy bỏ mục tiêu đối với bạn.\n2. Ngoài lượt của bạn, khi bạn nhận được bài do người chơi khác giao cho, đặt những lá bài này lên trên Tướng này, gọi là [Cầm]. Đầu giai đoạn rút bài, bạn nhận lấy tất cả lá [Cầm]",
	["#GuanxingResult"] = "%from đã phát động \"<font color=\"yellow\"><b>Quan Tinh</b></font>\": %arg lên trên, %arg2 xuống dưới",
	["$GuanxingTop"] = "Đặt lên đầu chồng bài: %card",
	["$GuanxingBottom"] = "Đặt dưới đáy chồng bài: %card",
	["zither"] = "Cầm",

	["#zhaoyun"] = "Hổ Uy Tướng Quân",
	["zhaoyun"] = "Triệu Vân",
	["longdan"] = "Long Đảm",
	[":longdan"] = "1. Có thể sử dụng hoặc đánh ra [Thiểm] như [Sát], nếu như [Sát] này bị triệt tiêu bởi [Thiểm] của mục tiêu, có thể gây 1 sát thương cho 1 người chơi trừ mục tiêu.\n2. Có thể sử dụng hoặc đánh ra [Sát] như [Thiểm], nếu như [Thiểm] này triệt tiêu [Sát] của 1 người chơi, có thể hồi 1 máu cho 1 người chơi khác ngoại trừ người sử dụng [Sát].",

	["#longdan-draw"] = "Long đảm [Rút bài]",
	["#LongdanDraw"] = "%from đã phát động \"%arg<font color=\"yellow\"><b>(Ngũ Hổ Tướng Đại Kỳ)</b></font>\", rút 1 lá.",
	["longdan-damage"] = "Phát động \"Long Đảm\", gây 1 sát thương cho người chơi khác?",
	["longdan-recover"] = "Phát động \"Long Đảm\", hồi 1 máu cho người chơi khác?",
	["#longdan-slash"] = "Long Đảm [Sát]",
	["#longdan-jink"] = "Long Đảm [Tránh]",
	["#LongdanDamage"] = "%from đã phát động \"%arg\"，gây 1 sát thương cho %to",
	["#LongdanRecover"] = "%from đã phát động \"%arg\"，hồi 1 máu cho %to",
	
	["#machao"] = "Nhất Kỵ Đươmg Thiên",
	["machao"] = "Mã Siêu",
	["mashu_machao"] = "Mã Thuật",
	[":mashu"] = "Tỏa định kỹ, Khoảng cách từ bạn đến người chơi khác -1.",
	["tieqi"] = "Thiết Kỵ",
	[":tieqi"] = "Sau khi bạn xác định từng mục tiêu của [Sát], có thể tiến hành phán xét, sau đó vô hiệu hóa kỹ năng không phải Tỏa định kỹ của 1 tướng đã mở của mục tiêu trong lượt này; sau đó nếu mục tiêu không bỏ 1 lá cùng chất với phán xét, mục tiêu không thể sử dụng [Thiểm].",
	
	["@tieji-discard"] = "Thiết Kỵ: Bỏ 1 lá bài có chất %arg, nếu không bạn không thể sử dụng [Thiểm]",
	["#TieqiHeadSkills"] = "%from đã phát động \"%arg\", khóa kỹ năng không phải tỏa định kỹ của chủ tướng của %to",
	["#TieqiDeputySkills"] = "%from đã phát động \"%arg\", khóa kỹ năng không phải tỏa định kỹ của phó tướng của %to",
	["#TieqiAllSkills"] = "%from đã phát động \"arg\", khóa kỹ năng không phải tỏa định kỹ của %to ",
	
	
	["#huangyueying"] = "Quy Ẩn Kiệt Nữ",
	["huangyueying"] = "Hoàng Nguyệt Anh",
	["jizhi"] = "Tập Trí",
	[":jizhi"] = "Khi sử dụng công cụ phổ thông không chuyển hóa, có thể rút 1 lá bài.",
	["qicai"] = "Kỳ Tài",
	[":qicai"] = "Tỏa định kỹ, có thể sử dụng công cụ không hạn chế khoảng cách.",

	["#huangzhong"] = "Lão Đương Ích Tráng",
	["huangzhong"] = "Hoàng Trung",
	["liegong"] = "Liệt Cung",
    [":liegong"] = "Lá [Sát] của bạn không hạn chế khoảng cách khi sử dụng với mục tiêu có bài trên tay không nhiều hơn bạn. Sau khi bạn xác định từng mục tiêu của [Sát], nếu số máu của họ không ít hơn bạn, bạn có thể chọn:\n1. Lệnh mục tiêu không thể sử dụng [Thiểm] để hưởng ứng [Sát] này;\n2. Lệnh cho sát thương từ lá [Sát] này +1 đối với mục tiêu này.",
    ["@liegong-choice"] = "Liệt Cung: Lựa chọn hiệu quả cho %dest",
    ["liegong:nojink"] = "Không thể sử dụng [Thiểm]",
    ["liegong:adddamage"] = "Sát thương +1",

	["#weiyan"] = "Thị Huyết Độc Lang",
	["weiyan"] = "Ngụy Diên",
	["kuanggu"] = "Cuồng Cốt",
	[":kuanggu"] = "Sau khi gây 1 sát thương cho 1 mục tiêu trong tầm 1, hồi 1 máu hoặc rút 1 lá.",
	["kuanggu:draw"] = "Rút 1 lá",
	["kuanggu:recover"] = "Hồi 1 máu",
	
	["#pangtong"] = "Phượng Sồ",
	["pangtong"] = "Bàng Thống",
	["lianhuan"] = "Liên Hoàn",
	[":lianhuan"] = "Giai đoạn hành động, có thể sử dụng lá Tép trên tay như [Thiết Tác Liên Hoàn] hoặc đổi lấy 1 lá bài mới.",
	["niepan"] = "Niết Bàn",
	[":niepan"] = "Hạn định kỹ: Khi trong trạng thái hấp hối, có thể bỏ toàn bộ bài trong vùng chơi, loại bỏ các trạng thái, sau đó rút 3 lá và hồi máu đến 3.",
	["@nirvana"] = "Niết Bàn",

	["#wolong"] = "Ngoạ Long",
	["wolong"] = "Khổng Minh",
	["&wolong"] = "Gia Cát Lượng",
	["bazhen"] = "Bát Trận",
	[":bazhen"] = "Tỏa định kỹ, nếu vùng trang bị của bạn không có phòng cụ, xem như có [Bát Quái Trận].",
	["huoji"] = "Hoả Kế",
	[":huoji"] = "Có thể dùng lá Đỏ trên tay như [Hoả Công].",
	["kanpo"] = "Khán Phá",
	[":kanpo"] = "Có thể dùng lá Đen trên tay như [Vô Giải Khả Kích].",

	["#liushan"] = "Vô Vi Chân Mệnh Chủ",
	["liushan"] = "Lưu Thiện",
	["xiangle"] = "Hưởng Lạc",
	[":xiangle"] = "Tỏa định kỹ, sau khi trở thành mục tiêu của [Sát], người sử dụng phải bỏ thêm 1 lá cơ bản nếu không [Sát] đó bị vô hiệu với bạn.",
	["@xiangle-discard"] = "%src đã phát động [Hưởng Lạc], hãy bỏ thêm 1 lá cơ bản nếu không lá [Sát] sẽ vô hiệu.",
	["fangquan"] = "Ủy Quyền",
	[":fangquan"] = "Có thể bỏ qua giai đoạn hành động và bỏ 1 lá bài trên tay khi kết thúc lượt để lệnh một người chơi có 1 lượt chơi.",
	["@fangquan-discard"] = "Bạn có thể bỏ ra 1 lá bài và chọn 1 người chơi để họ có lượt sau bạn.",
	["#fangquan-after"] = "Ủy Quyền",
	["~fangquan"] = "Chọn 1 lá bài, chọn 1 người chơi và kích \"Xác nhận\"",
	["#Fangquan"] = "%to đã nhận lượt thay thế",

	["#menghuo"] = "Nam Man Vương",
	["menghuo"] = "Mạnh Hoạch",
	["huoshou"] = "Chủ Mưu",
	[":huoshou"] = "Tỏa định kỹ, [Nam Man Nhập Xâm] không có hiệu quả với bạn, Sau khi 1 người chơi sử dụng [Nam Man Nhập Xâm] chỉ định mục tiêu, bạn trở thành nguồn sát thương của [Nam Man Nhập Xâm] này.",
	["#sa_avoid_huoshou"] = "Chủ Mưu (vô hiệu Nam Man Nhập Xâm)" ,
	["zaiqi"] = "Tái Khởi",
    [":zaiqi"] = "Kết thúc giai đoạn bỏ bài, bạn có thể chọn tối đa X người cùng thế lực, họ lựa chọn rút 1 lá hoặc lệnh cho bạn hồi 1 máu (X là số lá Đỏ đi vào chồng bài bỏ trong lượt này)",
	["#HuoshouTransfer"] = "%from đã phát động \"%arg2\", [<font color=\"yellow\"><b>Nam Man Nhập Xâm</b></font>] chuyển nguồn sát thương thành %from",
	["@zaiqi-target"] = "Có thể phát động \"Tái Khởi\", chọn tối đa %arg người cùng thế lực với bạn",
    ["@zaiqi-choice"] = "Tái khởi: Rút 1 lá hoặc Lệnh cho %src hồi 1 máu",
    ["zaiqi:drawcard"] = "Rút 1 lá",
    ["zaiqi:recover"] = "Hồi 1 máu",

	["#zhurong"] = "Dã Tính Nữ Vương",
	["zhurong"] = "Chúc Dung",
	["juxiang"] = "Cự Tượng",
	[":juxiang"] = "Tỏa định kỹ, vô hiệu hoá [Nam Man Nhập Xâm] lên bản thân; sau khi [Nam Man Nhập Xâm] kết toán xong, thu lấy lá này.",
	["#sa_avoid_juxiang"] = "Cự Tượng vô hiệu hoá [Nam Man Nhập Xâm]" ,
	["lieren"] = "Liệt Nhận",
	[":lieren"] = "Sau khi gây sát thương cho mục tiêu của [Sát], có thể tiến hành đấu điểm. Nếu thắng, bạn thu lấy 1 lá bài của mục tiêu.",

	["#ganfuren"] = "Chiêu Liệt Hoàng Hậu",
	["ganfuren"] = "Cam Phu Nhân",
	["shushen"] = "Thục Thận",
	[":shushen"] = "Sau khi hồi 1 máu, có thể chọn một người chơi khác, người đó rút 1 lá.",
	["shushen-invoke"] = "Phát động \"Thục Thận\". <br/>Chọn một người chơi rồi bấm \"Xác nhận\"<br/>",
	["shenzhi"] = "Thần Trí",
	[":shenzhi"] = "Giai đoạn chuẩn bị, có thể bỏ tất cả bài trên tay, nếu số lá bỏ đi lớn hơn hoặc bằng số máu hiện tại, bạn hồi 1 máu.",

	

}
