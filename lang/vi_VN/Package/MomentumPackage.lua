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

-- translation for Hegemony Momentum Package

return {
	["momentum"] = "Thế",
	["momentum_equip"] = "Thế",

	["#lidian"] = "Thâm Minh Đại Nghĩa",
	["lidian"] = "Lý Điển",
	["xunxun"] = "Tuân Tuân",
	[":xunxun"] = "Khi bắt đầu giai đoạn rút bài, bạn có thể xem 4 lá trên đầu chồng bài rút, sau đó đặt 2 lá trong số đó lên đầu chồng bài rút, còn lại đặt xuống đáy chồng bài rút.",
	["@xunxun"] = "Đặt 2 lá lên đầu chồng bài, còn lại xếp vào đáy chồng bài.",
	["xunxun#up"] = "Đáy chồng bài",
	["xunxun#down"] = "Đầu chồng bài",
	["#XunxunResult"] = "Kết quả \"<font color=\"yellow\"><b>Tuân Tuân</b></font>\" của %from: <font color=\"yellow\"><b>2</b></font> trên <font color=\"yellow\"><b>2</b></font> dưới",
	["wangxi"] = "Vong Khích",
	[":wangxi"] = "Sau khi bạn gây/nhận sát thương cho/từ người chơi khác, ứng với mỗi sát thương, bạn có thể lệnh bạn và họ rút 1 lá.",

	["#zangba"] = "Tiết Độ Thanh Từ",
	["zangba"] = "Tang Bá",
	["hengjiang"] = "Hoành Giang",
	[":hengjiang"] = "* Sau khi bạn nhận sát thương, ứng với mỗi sát thương, nếu giới hạn trữ bài của người đang có lượt > 0, bạn có thể lệnh người đang có lượt giảm 1 giới hạn trữ bài.\n* Khi kết thúc lượt, nếu ở giai đoạn bỏ bài, họ không bỏ lá nào, bạn rút X lá bài (X là số lần bạn đã phát động \"Hoành Giang\" trong lượt này).",
	["@hengjiang"] = "Hoành Giang",
	["#HengjiangDraw"] = "%from không bỏ bài, %to phát động hiệu quả [%arg]",
	["#hengjiang-draw"] = "Hoành Giang (Rút bài)",

	["#madai"] = "Lâm Nguy Thụ Mệnh",
	["madai"] = "Mã Đại",
	["mashu_madai"] = "Mã Thuật",
	["qianxi"] = "Tiềm Tập",
	[":qianxi"] = "Giai đoạn chuẩn bị, bạn có thể rút 1 lá, sau đó bỏ 1 lá và chọn 1 người khác ở khoảng cách 1, họ không thể sử dụng hoặc đánh ra lá trên tay cùng màu với lá bạn đã bỏ đến sau khi kết thúc lượt này.",
	["@qianxi-discard"] = "Tiềm tập: Chọn 1 lá để bỏ.",
	["@qianxi-choose"] = "Tiềm tập: Chọn 1 người chơi khác.",
	["#Qianxi"] = "Phát động hiệu quả <font color=\"yellow\"><b>\"Tiềm Tập\"</b></font>, trong lượt %from không thể dùng hoặc xuất ra bài %arg",
	["@qianxi_red"] = "Tiềm Tập (Đỏ)",
	["@qianxi_black"] = "Tiềm Tập (Đen)",

	["#mifuren"] = "Loạn Thế Trầm Hương",
	["mifuren"] = "My Phu Nhân",
	["guixiu"] = "Khuê Tú",
	[":guixiu"] = "* Sau khi mở tướng này, bạn có thế rút 2 lá.\n* Sau khi tướng này bị loại bỏ, bạn có thể hồi 1 máu.",
	["guixiu:draw"] = "Phát động \"Khuê Tú\", bốc 2 lá bài.",
	["guixiu:recover"] = "Phát động \"Khuê Tú\", hồi 1 máu.",
	["cunsi"] = "Tồn Tự",
	[":cunsi"] = "Giai đoạn hành động, bạn có thể loại bỏ tướng này; Sau đó, bạn chọn 1 người nhận kỹ năng \"Dũng Quyết\"; nếu người đó không phải bạn, họ rút 2 lá bài.",
	["yongjue"] = "Dũng Quyết",
	[":yongjue"] = "Sau khi kết toán xong [Sát] do người cùng thế lực với bạn sử dụng trong giai đoạn hành động, nếu lá này là lá đầu tiên họ sử dụng trong giai đoạn này, bạn có thể cho người đó thu lấy lá [Sát] này.",
	["@yongjue-choose"] = "\"Dũng Quyết\": Cho phép %src lấy lại lá [Sát]",
	
	["#sunce"] = "Giang Đông Đích Tiểu Bá Vương",
	["sunce"] = "Tôn Sách",
	["jiang"] = "Hùng Dũng",
	[":jiang"] = "Sau khi bạn xác định hoặc trở thành mục tiêu của [Sát] Đỏ hoặc [Quyết đấu], bạn có thể rút 1 lá.",
	["yingyang"] = "Ưng Dương",
	[":yingyang"] = "Sau khi mở lá đấu điểm của bạn, bạn có thể lệnh lá này +3 hoặc -3 điểm trong lần đấu điểm này (Lớn nhất là K, nhỏ nhất là A).",
	["jia3"] = "+3",
	["jian3"] = "-3",
	["$Yingyang"] = "Số điểm của %from trở thành %arg",
	["hunshang"] = "Hồn Thương",
	[":hunshang"] = "Phó tướng kỹ, Giảm 0.5 máu gốc: Giai đoạn chuẩn bị, nếu máu của bạn là 1, bạn có kỹ năng \"Anh Tư\" và \"Anh Hồn\" đến sau khi kết thúc lượt",
	["yingzi_sunce"] = "Anh Tư",
	["yinghun_sunce"] = "Anh Hồn",
	["#yinghun_sunce"] = "Phát động \"Anh Hồn\" lên %to",
	["yinghun_sunce:d1tx"] = "Rút 1 lá bài, sau đó bỏ %log lá bài.",
	["yinghun_sunce:dxt1"] = "Rút %log lá bài, sau đó bỏ 1 lá bài.",

	["#chenwudongxi"] = "Tráng Hoài Kích Liệt",
	["chenwudongxi"] = "Trấn Vũ & Đổng Tập",
	["&chenwudongxi"] = "Trấn Vũ Đổng Tập",
	["duanxie"] = "Đoạn Tiết",
	[":duanxie"] = "Một lần trong giai đoạn hành động, có thể lệnh X người không trong trạng thái xích nhận trạng thái xích (X là số máu đã mất của bạn, tối thiểu 1), sau đó đưa bạn nhận trạng thái xích.",
	["fenming"] = "Phấn Mệnh",
	[":fenming"] = "Giai đoạn kết thúc, nếu bạn trong trạng thái xích, bạn có thể bỏ đi 1 lá của những người trong trạng thái xích.",

	["#dongzhuo"] = "Ma Vương",
	["dongzhuo"] = "Đổng Trác",
	["hengzheng"] = "Hoàng Chinh",
	[":hengzheng"] = "Khi bắt đầu giai đoạn rút bài, nếu số máu của bạn là 1 hoặc không có bài trên tay, bạn có thể không rút bài, thu lấy từ mỗi người khác 1 lá trong vùng chơi.",
	["baoling"] = "Bạo Lăng",
	[":baoling"] = "Chủ tướng kỹ, Hạn định kỹ, Tỏa định kỹ: Khi bạn kết thúc giai đoạn hành động, nếu bạn đã mở tướng này và có phó tướng, loại bỏ phó tướng, sau đó bạn tăng giới hạn máu thêm 3, hồi 3 máu, nhận kỹ năng \"Băng Hoại\"",
	["benghuai"] = "Băng Hoại",
	[":benghuai"] = "Tỏa định kỹ: Giai đoạn kết thúc, nếu bạn không phải là người có số máu thấp nhất, bạn chọn mất 1 máu hoặc giảm 1 giới hạn máu.",
	["benghuai:hp"] = "Mất 1 máu" ,
	["benghuai:maxhp"] = "Giảm 1 giới hạn máu" ,

	["#zhangren"] = "Tác Mệnh Thần Xạ",
	["zhangren"] = "Trương Nhiệm",
	["chuanxin"] = "Xuyên Tâm",
	[":chuanxin"] = "Giai đoạn hành động của bạn, khi bạn gây sát thương cho mục tiêu của [Sát] hoặc [Quyết Đấu], nếu họ có thế lực xác định khác với bạn (bạn có thể mở tướng này để xác định khác thế lực), nếu mục tiêu có Phó tướng, bạn có thể chặn sát thương này, lệnh mục tiêu chọn 1 mục:\n1. Họ bỏ toàn bộ bài trong vùng Trang Bị (ít nhất 1 lá) và mất 1 máu.\n2. Họ loại bỏ Phó tướng.",
	["@chuanxin-choose"] = "Xuyên Tâm: Lựa chọn bỏ trang bị và mất 1 máu hoặc loại phó tướng",
	["chuanxin:discard"] = "Bỏ trang bị và mất 1 máu",
	["chuanxin:remove"] = "Loại bỏ Phó tướng",
	["fengshi"] = "Phong Thỉ",
	[":fengshi"] = "Trận pháp kỹ, nếu bạn là người vây công trong quan hệ vây công, sau khi người vây công xác định từng mục tiêu của lá [Sát], nếu mục tiêu này là người bị vây công, lệnh họ bỏ 1 lá trong vùng trang bị.",
	["@fengshi-discard"] = "%src đã phát động \"Phong Thỉ\", bỏ đi 1 lá trong vùng trang bị." ,
	["FengshiSummon"] = "Phong Thỉ",

	["#lord_zhangjiao"] = "Thời Đại Đích Tiên Khu",
	["lord_zhangjiao"] = "Trương Giác - Quân",
	["&lord_zhangjiao"] = "Trương Giác" ,
	["wuxin"] = "Ngộ Tâm",
	[":wuxin"] = "Đầu giai đoạn rút bài, có thể xem X lá đầu chồng bài rút và sắp xếp tùy ý những lá này lên đầu chồng bài rút (X là số người cùng thế lực với bạn).",
	["hongfa"] = "Hoằng Pháp",
	[":hongfa"] = "Quân chủ kỹ, Tỏa định kỹ: Bạn có \"Hoàng Cân Thiên Bình Phủ\".",
	["heavenly_army"] = "Thiên Binh",
	
	["huangjinsymbol"] = "Hoàng Cân Thiên Bình Phủ",
	[":huangjinsymbol"] = "* Giai đoạn chuẩn bị, nếu bạn không có [Thiên Binh], bạn lấy X lá đầu chồng bài rút đặt ngửa lên tướng này, gọi là [Thiên Binh] (X là số người có thế lực Quần).\n" ..
					"* Khi bạn tính toán số người cùng thế lực với bạn, +1 với mỗi [Thiên Binh].\n" ..
					"* Khi bạn mất máu, bạn có thể đưa 1 [Thiên Binh] vào chồng bài bỏ, chặn việc mất máu.\n" ..  
					"* Người thế lực Quần có thể chuyển hóa sử dụng/đánh ra [Thiên Binh] thành [Sát].",
	
	["&huangjinsymbol"] = "Có thể chuyển hóa 1 [Thiên Binh] thành [Sát]",
	["#HongfaTianbing"] = "%from đã phát động \"<font color=\"yellow\"><b>Hoàng Cân Thiên Bình Phủ</b></font>\", số người trong thế lực Quần là %arg.",
	["wendao"] = "Vấn Đạo",
	[":wendao"] = "Một lần trong giai đoạn hành động, bạn có thể bỏ 1 lá Đỏ ngoại trừ [Thái Bình Yêu Thuật] và thu lấy [Thái Bình Yêu Thuật] trong chồng bài bỏ hoặc trên bàn chơi.",
	["huangjinsymbol:prevent"] = "Có thể phát động \"Hoằng Pháp\", bỏ 1 [Thiên Binh] để chặn mất máu.",
	["@huangjinsymbol-discard"] = "Bỏ 1 [Thiên Binh]",
	["@hongfa-tianbing"] = "<font color='#ffcc33'><b>%src</b></font> Có thể phát động \"Hoằng Pháp\", số người trong thế lực Quần +X",
	["~hongfa2"] = "Lựa chọn X lá [Thiên Binh], bấm \"Xác nhận\"",

	["PeaceSpell"] = "Thái Bình Yêu Thuật",
	[":PeaceSpell"] = "Bài trang bị - Phòng cụ\n\nKỹ năng: Tỏa định kỹ:\n" ..
					"* Khi bạn nhận sát thương có thuộc tính, bạn chặn sát thương này.\n" ..
					"* Giới hạn trữ bài của bạn +X (X là số người cùng thế lực với bạn).\n" ..
					"* Khi bạn mất đi [Thái Bình Yêu Thuật] từ vùng trang bị, bạn rút 2 lá, sau đó nếu máu của bạn lớn hơn 1, bạn mất 1 máu.\n" ,
	["#PeaceSpellNatureDamage"] = "[<font color=\"yellow\"><b>Thái Bình Yêu Thuật</b></font>] đã phát động, chặn sát thương từ %from gây cho %to %arg sát thương." ,
	["#PeaceSpellLost"] = "%from đã mất [<font color=\"yellow\"><b>Thái Bình Yêu Thuật</b></font>] khỏi vùng trang bị, rút 2 lá." ,


}
