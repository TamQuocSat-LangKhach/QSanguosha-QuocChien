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
	["manoeuvre"] = "Tung Hoành Bãi Hạp",
	
	["#huaxin"] = "Uyên Thanh Ngọc Khiết",
	["huaxin"] = "Hoa Hâm",
	["wanggui"] = "Vong Quy",
	[":wanggui"] = "Một lần trong lượt của mỗi người, sau khi bạn gây hoặc nhận sát thương và bạn đã mở tướng này, nếu tướng còn lại của bạn:\nChưa mở: có thể gây 1 sát thương cho người không cùng thế lực.\nĐã mở: có thể lệnh những người cùng thế lực rút 1 lá.",
	["wanggui:prompt"] = "Có thể kích \"Vong Quy\", người cùng thế lực rút 1 lá.",
	["wanggui-invoke"] = "Có thể kích \"Vong Quy\", gây 1 sát thương cho người không cùng thế lực.",
	["xibing"] = "Tức Binh",
	[":xibing"] = "Sau khi 1 người khác lần đầu trong giai đoạn hành động của họ sử dụng [Sát] đen hoặc công cụ phổ thông đen và chỉ định 1 mục tiêu duy nhất, bạn có thể phát động kỹ năng này và thực hiện lần lượt:\n1. Nếu bài trên tay họ nhỏ hơn số máu của họ, bạn lệnh họ bổ sung bài trên tay đến số máu của họ và không thể tiếp tục sử dụng bài trên tay trong lượt này\n2. Nếu bạn và họ đã mở tất cả tướng, bạn có thể úp 1 tướng của bạn và họ, trong lượt này không thể mở lại tướng đó.",
	["@xibing-hide"] = "Tức Binh: Chọn tướng của %dest để úp.",
	["xibing:head"] = "Chủ tướng",
	["xibing:deputy"] = "Phó tướng",
	
	["#luyusheng"] = "Nghĩa Cô",
	["luyusheng"] = "Lục Úc Sinh",
	["zhente"] = "Trinh Đặc",
	[":zhente"] = "Một lần trong lượt của mỗi người, sau khi trở thành mục tiêu của lá cơ bản Đen hoặc công cụ phổ thông Đen từ người khác, có thể lệnh cho họ chọn 1 mục:\n1. Lượt này họ không thể sử dụng bài Đen.\n2. Lá này không có hiệu quả với bạn.",

	["zhente-ask"] = "Trinh Đặc: 1. Vô hiệu [%arg] với %src; 2. Không thể sử dụng bài đen trong lượt này.",
	["zhente:nullified"] = "Vô hiệu cho mục tiêu",
	["zhente:cardlimited"] = "Lượt này không sử dụng bài đen",
	
	["#ZhenteChoice1"] = "%from đã chọn: [%arg] vô hiệu với %to",
	["#ZhenteChoice2"] = "%from đã chọn: Lượt này không sử dụng bài đen",

	
	["zhiwei"] = "Chi Vi",
	[":zhiwei"] = "Sau khi bạn mở tướng này, có thể chọn 1 người khác. Đến khi tướng này bị úp hoặc loại bỏ; Sau khi họ gây sát thương, bạn rút 1 lá; Sau khi họ nhận sát thương, bạn bỏ 1 lá ngẫu nhiên trên tay; Giai đoạn bỏ bài, bạn lệnh họ thu lấy tất cả bài bỏ của bạn. Khi họ trận vong, nếu bạn đã mở tất cả tướng, bạn úp tướng này.",
	
	["zhiwei-invoke"] = "Có thể phát động \"Chi Vi\", chọn 1 người khác.",
	
	["#ZhiweiEffect1"] = "%to đã gây sát thương, %from đã kích \"%arg\" và rút 1 lá",
	["#ZhiweiEffect2"] = "%to đã nhận sát thương, %from đã kích \"%arg\" và bỏ 1 lá",
	["#ZhiweiEffect3"] = "%to đã thu lấy bài bỏ của %from bởi \"%arg\"",
	["#ZhiweiEffect4"] = "%to đã trận vong, %from đã úp tướng bởi \"%arg\"",
	
	["#ZhiweiFinsh"] = "%from đã kết thúc kỹ năng \"%arg\" với %to",
	
	["#zongyux"] = "Cửu Uẩn Hồng Lư",
    ["zongyux"] = "Tông Dự",
    ["qiao"] = "Khí Ngạo",
    [":qiao"] = "Hai lần trong giai đoạn hành động của mỗi người, sau khi bạn trở thành mục tiêu của bài do người khác thế lực sử dụng, có thể bỏ 1 lá của họ, sau đó bạn bỏ 1 lá.",
    ["chengshang"] = "Thừa Thưởng",
    [":chengshang"] = "Một lần trong giai đoạn hành động, sau khi bài bạn sử dụng chỉ định người khác thế lực làm mục tiêu kết toán xong, nếu số lá được đem sử dụng là 1 và lá này không gây sát thương, có thể thu lấy những lá có cùng chất và điểm với lá đó trong chồng bài rút; nếu bạn không thu được bài sau khi phát động kỹ năng, xem như bạn chưa phát động kỹ năng này trong giai đoạn này.",

    ["@qiao-discard"] = "Khí Ngạo: Bỏ 1 lá.",
    
    ["#miheng"] = "Cuồng Ngạo Kì Nhân",
    ["miheng"] = "Nễ Hành",
    ["kuangcai"] = "Cuồng Tài",
    [":kuangcai"] = "Tỏa định kỹ, bài bạn sử dụng trong lượt không bị giới hạn khoảng cách và số lần sử dụng; đầu giai đoạn bỏ bài, nếu trong lượt này bạn có sử dụng bài và không gây sát thương, giới hạn trữ bài trở về sau -1; nếu bạn không sử dụng bài, giới hạn trữ bài trở về sau +1.",
    ["shejian"] = "Thiệt Kiếm",
    [":shejian"] = "Sau khi bạn trở thành mục tiêu duy nhất của bài do người khác sử dụng, nếu không có ai đang giải quyết hấp hối, có thể bỏ tất cả bài trên tay (tối thiếu 1), chọn 1 mục:\n1. Bỏ X lá của người sử dụng bài (X là số lá bạn đã bỏ).\n2. Gây 1 sát thương cho người sử dụng bài.",
	["decrease"] = " -",
    ["increase"] = " +",
	
	["@shejian-choice"] = "Thiệt Kiếm: Chọn bỏ %arg lá của %dest hoặc gây 1 sát thương cho %dest",
    ["shejian:discard"] = "Bỏ bài",
    ["shejian:damage"] = "Gây sát thương",
    
    ["MOL"] = "Mobile",
    
    
    ["#duyu"] = "Văn Thành Võ Đức",
    ["duyu"] = "Đỗ Dự",
    ["wuku"] = "Vũ Khố",
    [":wuku"] = "Tỏa định kỹ, khi 1 người không cùng thế lực sử dụng 1 trang bị, bạn thu lấy 1 tiêu ký [Võ Khố] (Tối đa 2).",
    ["miewu"] = "Diệt Ngô",
    [":miewu"] = "Một lần trong lượt của mỗi người, có thể bỏ 1 [Võ Khố], sau đó sử dụng/đánh ra 1 lá bài như 1 lá cơ bản hoặc công cụ tùy ý; sau đó, bạn rút 1 lá.",
    ["#armory"] = "Vũ Khố",
	
	["overseas"] = "SP",
	["removed"] = "SP - Tiêu Trừ",

	["beimihu"] = "Himiko",
	["#beimihu"] = "Yamatai Đích Nữ Vương",
	["guishu"] = "Quỷ Thuật",
	[":guishu"] = "Có thể sử dụng 1 lá Bích trên tay như [Tri Bỉ Tri Kỷ] hoặc [Viễn Giao Cận Công]. Bạn cần sử dụng xen kẽ 2 lá bài trên trong cùng 1 lượt." ,
	["yuanyu"] = "Viễn Vực",
	[":yuanyu"] = "Tỏa định kỹ, khi nhận sát thương, nếu bạn không nằm trong  trong tầm đánh của nguồn sát thương, sát thương này -1.",

	["caozhen"] = "Tào Chân",
	["#caozhen"] = "Vạn Tải Bất San",
	["sidi"] = "Ty Địch",
	[":sidi"] = "Sau khi người cùng thế lực với bạn nhận sát thương, nếu họ có bài và số loại bài [Ngự] của bạn nhỏ hơn 3, bạn có thể phát động kỹ năng, họ có thể đặt 1 lá bài của họ lên tướng của bạn, gọi là [Ngự] (Không được chọn lá cùng loại với những lá [Ngự] đã có). Khi bắt đầu lượt của người khác thế lực, bạn có thể đưa tối đa 3 [Ngự] vào chồng bài bỏ, đưa ra số lựa chọn tương ứng:\n"..
	"1. Bạn chọn 1 loại bài tương ứng với loại bài của [Ngự] vừa bỏ, họ trong lượt này không thể sử dụng loại bài này.\n2. Bạn chọn 1 kỹ năng của tướng đã lật của họ, vô hiệu kỹ năng đó trong lượt này.\n3. Bạn lệnh họ chọn 1 người khác cùng thế lực với bạn, họ hồi 1 màu.",

	["drive"] = "Ngự",

	["@sidi-put"] = "Ty Địch: Có thể chọn 1 lá đặt lên %src để làm [Ngự]",
	["@sidi-remove"] = "Có thể phát động \"Ty Địch\" với %dest",
	["@sidi-choice"] = "Ty Địch: Đưa ra lựa chọn để %dest chấp hành",

	["sidi_choice:cardlimit"] = "Không sử dụng 1 loại bài",
	["sidi_choice:skilllimit"] = "Vô hiệu 1 kỹ năng",
	["sidi_choice:recover"] = "Chọn người để hồi máu",

	["@sidi-recover"] = "Ty Địch: Chọn 1 người để hồi máu.",
	["@sidi-cardtype"] = "Ty Địch: Lệnh %dest không được sử dụng 1 loại bài trong lượt này.",
	["@sidi-skill"] = "Ty Địch: Lệnh 1 kỹ năng của %dest vô hiệu trong lượt này.",


	["#liaohua"] = "Lịch Tận Thương Tang",
	["liaohua"] = "Liêu Hóa",
	["dangxian"] = "Đương Tiên",
	[":dangxian"] = "Tỏa định kỹ, sau khi lật tướng lần đầu tiên, bạn nhận 1 tiêu ký [Tiên Khu]. Sau khi bắt đầu lượt chơi, bạn nhận 1 giai đoạn hành động",

	["#zhugejin"] = "Liên Minh Đích Duy Hệ Giả",
	["zhugejin"] = "Gia Cát Cẩn",
	["huanshi"] = "Hoãn Thích",
	[":huanshi"] = "Trước khi 1 phán xét của người chơi cùng thế lực với bạn có hiệu lực, có thể đánh ra 1 lá bài để thay thế kết quả Phán xét đó.",
	["hongyuan"] = "Hoằng Viện",
	[":hongyuan"] = "Khi bạn rút bài vì hiệu quả của \"Hợp Tung\", bạn có thể lệnh 1 người khác cùng thế lực rút bài thay bạn. Một lần trong giai đoạn hành động, bạn có thể mở 1 lá trên tay, lá đó khi ở trên tay bạn trong giai đoạn này xem như có ký hiệu \"Hợp Tung\".",
	["mingzhe"] = "Minh Triết",
	[":mingzhe"] = "Ngoài lượt của bạn:\n1. Khi bạn sử dụng/đánh ra lá Đỏ, bạn có thể rút 1 lá.\n2. Khi bạn mất đi 1 lá Đỏ trong vùng trang bị, bạn có thể rút 1 lá",

	["@huanshi-card"] = CommonTranslationTable["@askforretrial"],
	["hongyuan-invoke"] = "Có thể phát động \"Hoằng Viện\", chọn 1 người nhận bài.",
	
	["#quancong"] = "Mộ Thế Diệu Tộc",
    ["quancong"] = "Toàn Tông",
    ["qinzhong"] = "Thân Trùng",
    [":qinzhong"] = "Phó tướng kỹ, đầu lượt, bạn có thể hoán đổi phó tướng với 1 người cùng thế lực",
    ["zhaofu"] = "Chiêu Phụ",
    [":zhaofu"] = "Đầu giai đoạn hành động, nếu tổng số [Thưởng] của tất cả người chơi nhỏ hơn 3, bạn có thể bỏ 1 lá và chọn 1 người khác, người đó nhận 1 tiêu ký [Thưởng]. Sau khi lá cơ bản/công cụ phổ thông do người có [Thưởng] sử dụng kết toán xong, bạn có thể lệnh người đó bỏ 1 tiêu ký [Thưởng], xem như bạn sử dụng lá đó.",

    ["reward"] = "Thưởng",
    
    ["qinzhong-invoke"] = "Có thể phát động \"Thân Trùng\", hoán đổi phó tướng với 1 người cùng thế lực.",
    ["@zhaofu1"] = "Có thể phát động \"Chiêu Phụ\", bỏ 1 lá để 1 người được nhận [Thưởng]",
    ["zhaofu:prompt"] = "Có thể phát động \"Chiêu Phụ\", xem như sử dụng [%arg]",
    ["@zhaofu2"] = "Có thể phát động \"Chiêu Phụ\", xem như sử dụng [%arg]",
	
	["#guohuai"] = "Thùy Vấn Tần Ung",
    ["guohuai"] = "Quách Hoài",
    ["jingce"] = "Tinh Sách",
    [":jingce"] = "Giai đoạn hành động, sau khi bạn sử dụng lá thứ X kết toán xong (X là máu hiện tại của bạn), nếu không có ai đang giải quyết hấp hối, bạn có thể lệnh 1 người khác thế lực chấp hành 1 [Quân Lệnh], nếu họ không chấp hành, bạn rút 2 lá.",
    ["jingce-invoke"] = "Có thể phát động \"Tinh Sách\", chọn 1 người khác thế lực chấp hành quân lệnh.",

    ["#yangxiu"] = "Thị Tài Phóng Khoáng",
    ["yangxiu"] = "Dương Tu",
    ["danlao"] = "Đạm Lạc",
    [":danlao"] = "Sau khi bạn trở thành mục tiêu của bài công cụ, nếu số mục tiêu nhiều hơn 1, bạn có thể rút 1 lá, lệnh lá đó vô hiệu với bạn.",
    ["jilei"] = "Kê Lặc",
    [":jilei"] = "Sau khi bạn nhận sát thương, nếu sát thương này có nguồn, bạn có thể chọn 1 loại bài, lệnh nguồn sát thương trong lượt này không thể sử dụng, đánh ra hoặc bỏ những lá trên tay thuộc loại bài này.",
    ["#Jilei"] = "\"<font color=\"yellow\"><b>Kê Lặc</b></font>\" có hiệu lực, %from không thể sử dụng, đánh ra hoặc bỏ %arg trên tay.",
    ["@jilei-choose"] = "Kê lặc: Chọn loại bài để %dest không thể sử dụng, đánh ra hoặc bỏ.",

    ["#zumao"] = "Bích Huyết Nhiễm Xích Trách",
    ["zumao"] = "Tổ Mậu",
    ["yinbingx"] = "Dẫn Binh",
    [":yinbingx"] = "Giai đoạn kết thúc, bạn có thể đặt tùy ý lá phi cơ bản lên tướng này, gọi là [Trách]. Sau khi bạn nhận sát thương từ [Sát] hoặc [Quyết Đấu], bạn bỏ 1 lá [Trách].",
    ["@yinbing-put"] = "Có thể phát động \"Dẫn Binh\", đặt 1 lá phi cơ bản là [Trách]",
    ["kerchief"] = "Trách",
    ["juedi"] = "Tuyệt Địa",
    [":juedi"] = "Tỏa định kỹ, Giai đoạn chuẩn bị, nếu bạn có [Trách], bạn chọn 1 mục:\n1. Bỏ tất cả lá [Trách], bổ xung bài trên tay tới giới hạn máu;\n2. Giao tất cả [Trách] cho 1 người khác có số máu không lớn hơn bạn, lệnh họ hồi 1 máu và rút bài bằng số [Trách] bạn đã giao.",
    ["juedi:self"] = "Bỏ [Trách] và bổ xung bài",
    ["juedi:give"] = "Giao [Trách] cho người khác",
    ["@juedi"] = "Tuyệt địa: Chọn 1 người khác có giới hạn máu không lớn hơn bạn.",

    ["#fuwan"] = "Trầm Nghị Đích Quốc Trượng",
    ["fuwan"] = "Phục Hoàn",
    ["moukui"] = "Mưu Hội",
    [":moukui"] = "Sau khi bạn chỉ định mục tiêu cho [Sát], có thể chọn 1 mục:\n1. Rút 1 lá;\n2. Bỏ 1 lá của mục tiêu của [Sát] này;\nNếu làm vậy, sau khi [Sát] bị triệt tiêu bởi [Thiểm] của mục tiêu, bạn lệnh họ bỏ 1 lá của bạn.",
    ["@moukui-choose"] = "Mưu Hội: Chọn rút 1 lá hoặc bỏ 1 lá của %dest",
    ["moukui:draw"] = "Rút 1 lá",
    ["moukui:discard"] = "Bỏ 1 lá",

    ["#MoukuiDiscard"] = "Đã phát động \"%arg\", %to bỏ 1 lá của %from",

    ["#chendao"] = "Bạch Nhị Đốc",
    ["chendao"] = "Trần Đáo",
    ["wanglie"] = "Vãng Liệt",
    [":wanglie"] = "Lá đầu tiên bạn sử dụng trong giai đoạn hành động không hạn chế khoảng cách. Giai đoạn hành động, khi bạn sử dụng [Sát] hoặc công cụ phổ thông, bạn có thể lệnh cho tất cả người chơi không được hưởng ứng với lá này; nếu làm vậy, bạn không thể sử dụng bài trong giai đoạn này.",
	["dizai"] = "Địa Tải",
	[":dizai"] = "Trận pháp kỹ, nếu bạn là người vây công trong quan hệ vây công, khi người vây công gây sát thương cho mục tiêu bị vây công của lá [Sát], người vây công còn lại có thể bỏ 1 lá để lệnh sát thương này +1.",
	["@dizai_discard"] = "Địa Tải: Có thể bỏ 1 lá để lệnh sát thương %src gây cho %dest +1",

    ["#tianyu"] = "Quy Lược Minh Luyện",
    ["tianyu"] = "Điền Dự",
    ["zhenxi"] = "Chấn Tập",
    [":zhenxi"] = "Sau khi bạn chỉ định mục tiêu cho [Sát], có thể chọn:\n1. Bỏ 1 lá của họ.\n2. Bạn có thể sử dụng 1 lá phi công cụ Tép như [Binh Lương Thốn Đoạn] hoặc 1 lá phi công cụ Rô như [Lạc Bất Tư Thục] không hạn chế khoảng cách với họ.\nNếu bạn đã mở 2 tướng và họ có tướng đang úp, bạn có thể chấp hành cả 2 mục với thứ tự tùy ý.",
    ["jiansu"] = "Kiệm Tố",
    [":jiansu"] = "Phó tướng kỹ, Giảm 0.5 máu gốc. Khi bạn nhận bài ngoài lượt, bạn có thể mở những lá này trên tay bạn, gọi là [Kim] chừng nào lá đó còn trên tay bạn; Những người chơi khác luôn nhìn thấy [Kim]. Đầu giai đoạn hành động, bạn có thể bỏ đi tùy ý lá [Kim], sau đó chọn 1 người đã bị thương có số máu không lớn hơn số [Kim] đã bỏ, lệnh họ hồi 1 máu.",
    ["@zhenxi-choose"] = "Chấn Tập: Chọn sử dụng 1 lá Công cụ thời gian đã chuyển hóa lên %dest hoặc bỏ 1 lá của họ.",
    ["zhenxi:usecard"] = "Chuyển hóa 1 công cụ thời gian",
    ["zhenxi:discard"] = "Bỏ 1 lá",
    ["@zhenxi-trick"] = "Chấn Tập: Sử dụng lá phi công cụ Rô như [Lạc Bất Tư Thục] hoặc phi công cụ Tép như [Binh Lương Thốn Đoạn] lên %dest",
    ["@zhenxi-discard"] = "Chấn Tập: Bỏ 1 lá của %dest",
    ["@jiansu-card"] = "Có thể phát động \"Kiệm Tố\", bỏ [Kim] và lệnh 1 người hồi máu.",
	["money"] = "Kim",


    ["#maliang"] = "Bạch Mi Lệnh Sĩ",
    ["maliang"] = "Mã Lương",
    ["mumeng"] = "Mục Minh",
    [":mumeng"] = "Một lần trong giai đoạn hành động, bạn có thể sử dụng 1 lá Cơ trên tay như [Viễn Giao Cận Công] hoặc [Lục Lực Đồng Tâm]",
    ["naman"] = "Nạp Man",
    [":naman"] = "Khi người khác sử dụng bài Đen chỉ định nhiều mục tiêu, bạn có thể tiến hành phán xét, nếu kết quả phát xét không phải Bích, bạn chọn:\n1. Lệnh 1 người khác trở thành mục tiêu của bài (Không bị giới hạn khoảng cách);\n2. Hủy bỏ mục tiêu đối với 1 mục tiêu của lá đó.",

    ["@naman-target"] = "Nạp Man: Thêm hoặc bớt 1 mục tiêu của [%arg] do %src sử dụng",
	
	["#huaxiong"] = "Ma Tướng",
    ["huaxiong"] = "Hoa Hùng",
    ["yaowu"] = "Diệu Võ",
    [":yaowu"] = "Hạn định kỹ, sau khi bạn gây sát thương, nếu tướng này đang úp mặt, bạn có thể phát động kỹ năng này. Thêm 2 giới hạn máu, hồi 2 máu; nếu làm vậy, sau khi bạn trận vong, tất cả người chơi cùng thế lực với bạn mất 1 máu.",
    ["shiyong"] = "Thị Dũng",
    [":shiyong"] = "Tỏa định kỹ, khi bạn nhận sát thương từ lá bài, nếu bạn chưa phát động \"Diệu Võ\" và lá gây ra sát thương không phải màu đỏ, bạn rút 1 lá; nếu bạn đã phát động \"Diệu Võ\" và lá gây sát thương không phải màu đen, nguồn sát thương rút 1 lá.",

    ["#zhangchunhua"] = "Lãnh Huyết Hoàng Hậu",
    ["zhangchunhua"] = "Trương Xuân Hoa",
    ["guojue"] = "Quả Quyết",
    [":guojue"] = "Sau khi bạn mở tướng này lần đầu tiên, bạn gây 1 sát thương cho 1 người khác. Khi 1 người khác tiến vào trạng thái hấp hối, nếu nguồn sát thương là bạn, bạn có thể bỏ 1 lá của họ.",
    ["shangshi"] = "Thương Thệ",
    [":shangshi"] = "Sau khi bạn nhận sát thương, bạn có thể chọn bỏ 1 lá hoặc giao X lá trên tay bạn cho 1 người khác; nếu làm vậy, bạn rút X lá. (X lá số máu bạn đã mất)",
    ["@guojue-damage"] = "Quả quyết: Chọn 1 người khác để gây 1 sát thương",
    ["@shangshi-card"] = "Có thể phát động \"Thương Thệ\", chọn bỏ 1 lá hoặc giao %arg lá trên tay cho 1 người khác",
    ["@shangshi-card-full"] = "Có thể phát động \"Thương Thệ\", chọn bỏ 1 lá",

	["#liufuren"] = "Khốc Đố Đích Hải Đường",
	["liufuren"] = "Lưu Phu Nhân",
	["zhuidu"] = "Truy Đố",
	[":zhuidu"] = "Một lần trong giai đoạn hành động, khi bạn gây sát thương, bạn có thể lệnh người nhận sát thương chọn 1 mục:\n1. Sát thương này +1;\n2. Bỏ đi tất cả bài trong vùng trang bị, tối thiểu 1;\nNếu họ có giới tính nữ, bạn có thể bỏ 1 lá, lệnh họ thực hiện cả 2 mục.",
	["shigong"] = "Kỳ Cung",
	[":shigong"] = "Hạn định kỹ, Ngoài lượt, khi bạn tiến vào trạng thái hấp hối, bạn có thể loại bỏ Phó tướng của bạn, sau đó lệnh người đang có lượt chọn 1 mục:\n1. Họ nhận 1 kỹ năng không phân loại từ lá tướng mà bạn vừa loại bỏ, lệnh bạn hồi máu đến tối đa;\n2. Lệnh bạn hồi đến 1 máu.",

	["@zhuidu-both"] = "Truy Đố: Có thể bỏ 1 lá và lệnh %dest thực hiện 2 mục",
	["zhuidu_choice"] = "Truy Đố",
	["zhuidu_choice:throw"] = "Bỏ tất cả bài trong vùng trang bị",
	["zhuidu_choice:damage"] = "Sát thương +1",
	
	["@shigong-choose"] = "Kỳ Cung: Có thể nhận 1 kỹ năng của %arg",
	    
    ["#yijibo"] = "Kiến lễ vu thế",
    ["yijibo"] = "Y Tịch",
    ["dingke"] = "Định Khoa",
    [":dingke"] = "Một lần trong lượt của mỗi người, sau khi 1 người cùng thế lực với bạn mất bài ngoài lượt không vì sử dụng hoặc đánh ra, bạn có thể chọn 1 mục:\n1. Giao 1 lá trên tay cho họ;\n2. Lệnh người đang có lượt bỏ 1 lá trên tay;\nNếu số [Âm dương ngư] của bạn nhỏ hơn giới hạn máu, bạn thu lấy 1 tiêu ký [Âm dương ngư].",
    ["jiyuan"] = "Cấp Viện",
    [":jiyuan"] = "Khi có người tiến vào trạng thái hấp hối hoặc sau khi có người được bạn giao bài do phát động \"Định Khoa\", bạn có thể lệnh người đó rút 1 lá.",

	["dingke-invoke"] = "Có thể phát động \"Định Khoa\", chọn %dest để lệnh họ bỏ 1 lá trên tay hoặc chọn người vừa mất bài để giao họ 1 lá trên tay",
    ["@dingke-give"] = "Định Khoa: Chọn 1 lá trên tay và giao cho %dest",
    
    ["#zhangyi"] = "Tranh Hổ",
    ["zhangyi"] = "Trương Dực",
    ["kangrui"] = "Kháng Nhuệ",
    [":kangrui"] = "Một lần trong giai đoạn hành động của 1 người cùng thế lực với bạn, khi họ sử dụng bài chỉ định 1 người khác làm mục tiêu duy nhất, bạn có thể hủy bỏ mục tiêu của lá đó, lệnh họ chọn 1 mục:\n1. Bổ sung bài trên tay đến khi có X lá ( X là số máu của họ), những người khác trong giai đoạn này không thể trở thành mục tiêu của bài do họ sử dụng; 2. Nếu không có người trong trạng thái hấp hối, lệnh mục tiêu ban đầu của lá đó xem như sử dụng [Quyết đấu] với họ, số sát thương của [Quyết đấu] này +1.",
    
    ["kangrui:prompt"] = "Có thể phát động \"Kháng Nhuệ\", hủy bỏ mục tiêu %dest từ lá [%arg] của %src",
    ["@kangrui-choose"] = "Kháng Nhuệ: Chọn bổ xung bài trên tay đến giới hạn máu hoặc lệnh %dest xem như sử dụng [Quyết Đấu] với bạn",
    ["kangrui:fillhandcards"] = "Bổ xung bài",
    ["kangrui:useduel"] = "Quyết Đấu",
    
    ["#chengpu"] = "Hổ Thủ",
    ["chengpu"] = "Trình Phổ",
    ["huxun"] = "Hổ Huân",
    [":huxun"] = "Khi 1 người kết thúc lượt, nếu trong lượt này có người rơi vào trạng thái hấp hối do bạn gây sát thương, bạn có thể chọn 1 mục: 1. Nếu bạn không phải người duy nhất có giới hạn máu cao nhất, thêm 1 giới hạn máu và hồi 1 máu; 2. Có thể di chuyển một lá trong vùng trang bị hoặc vùng phán xét của một người sang vùng chơi của một người khác.",
    ["yuancong"] = "Nguyên Tòng",
    [":yuancong"] = "Khi kết thúc giai đoạn hành động của 1 người cùng thế lực với bạn, nếu trong giai đoạn này họ không gây sát thương, họ có thể giao 1 lá cho bạn, sau đó bạn có thể sử dụng 1 lá trên tay.",
    
    ["huxun:gainmaxhp"] = "Tăng giới hạn máu",
    ["huxun:movecard"] = "Di chuyển 1 lá trên bàn chơi.",
    ["@huxun-move"] = "Hổ Huân: Có thể di chuyển 1 lá trên bàn chơi.",
    ["@yuancong"] = "Có thể phát động \"Nguyên Tòng\" của %src",
    ["@yuancong-usecard"] = "Nguyên Tòng: Có thể sử dụng 1 lá trên tay.",
    
    
    ["#chengyu"] = "Thái Sơn Phụng Nhật",
    ["chengyu"] = "Trình Dục",
    ["shefu"] = "Phục Binh",
    [":shefu"] = "Một lần trong giai đoạn hành động, bạn có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Phục Binh]. Khi 1 người khác sử dụng bài trên tay, bạn có thể đưa 1 [Phục Binh] có cùng tên với lá đó vào chồng bài bỏ, hủy bỏ hoàn toàn lá đó. Giai đoạn chuẩn bị, nếu số [Phục Binh] nhiều hơn 2, bạn đưa số [Phục Binh] vào chồng bài đỏ đến khi còn 2.",
    ["benyu"] = "Bí Dục",
    [":benyu"] = "Sau khi bạn nhận sát thương:\n* Nếu bài trên tay bạn ít hơn nguồn sát thương, bạn chọn 1 mục:\n1. Bổ xung bài trên tay đến khi bằng với họ, tối đa 5 lá;\n2. Lệnh họ bỏ đi bài trên tay đến khi bằng bạn, tối đa bỏ 5 lá.\n* Nếu bài trên tay bạn nhiều hơn nguồn sát thương, bạn có thể bỏ số bài trên tay bằng số bài trên tay họ +1, sau đó gây 1 sát thương cho họ.",

    ["#shefu-compulsory"] = "Phục Binh",
    ["ambush"] = "Phục Binh",
    ["@shefu-invoke"] = "Có thể phát động \"Phục Binh\", bỏ 1 [Phục Binh] có tên [%arg] để hủy bỏ hoàn toàn lá [%arg] do %src sử dụng",
    ["@shefu-remove"] = "Phục Binh: chọn 1 [Phục Binh] để bỏ",
	
	["@benyu-invoke"] = "Có thể phát động \"Bí Dục\", bỏ %arg lá trên tay để gây 1 sát thương cho %dest",
    ["@benyu-choose"] = "Bí Dục: Chọn phương pháp để bài trên tay bạn bằng với %dest",
    ["benyu:draw"] = "Bạn bổ xung bài",
    ["benyu:discard"] = "Họ bỏ bài",
	
	["#xiahoushang"] = "Ngụy Dận Tiền Khu",
	["xiahoushang"] = "Hạ Hầu Thượng",
	
	["tanfeng"] = "Tham Phong",
	[":tanfeng"] = "Đầu giai đoạn chuẩn bị, bạn có thể bỏ 1 lá trong vùng chơi của 1 người khác thế lực; nếu làm vậy, họ có thể chọn nhận 1 sát thương hỏa từ bạn để lệnh bạn bỏ qua 1 giai đoạn trong lượt này, ngoại trừ giai đoạn chuẩn bị.",
	["@tanfeng-target"] = "Có thể phát động \"Tham Phong\", chọn 1 người khác thế lực",
	["@tanfeng-choose"] = "Tham Phong: Có thể nhận 1 sát thương hỏa để lệnh %src bỏ qua 1 giai đoạn",


	["#guyong"] = "Miếu Đường Đích Ngọc Khách",
	["guyong"] = "Cố Ung",
	
	["lifu"] = "Lễ Phụ",
	[":lifu"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người, lệnh họ bỏ 2 lá, sau đó bạn xem lá trên cùng của chồng bài rút và giao cho họ.",
	["yanzhong"] = "Ngôn Trung",
	[":yanzhong"] = "Đầu giai đoạn kết thúc, bạn có thể chọn 1 chất và chọn 1 người khác có bài trên tay, bạn bỏ 1 lá trên tay họ; nếu chất của lá đã bỏ và chất đã đoán khác chất, bạn bỏ 1 lá; nếu cùng chất và chất đó là:\nCơ: Bạn hồi 1 máu;\nRô: Bạn rút 1 lá, loại bỏ trạng thái xích;\nTép: Họ giao 1 lá cho bạn;\nBích: Họ mất 1 máu.",
	["lifu_view:prompt"] = "Lễ Phụ: Lá [%arg] này sẽ được giao cho %dest",
	["@yanzhong"] = "Có thể phát động \"Ngôn Trung\", chọn 1 người khác có bài trên tay",
	["@yanzhong-give"] = "Ngôn Trung: Chọn 1 lá và giao cho %src",

	["#liyan"] = "Long Lý Toàn Vân",
	["liyan"] = "Lý Nghiêm",
	
	["jinwu"] = "Căng Võ",
	[":jinwu"] = "Đầu giai đoạn hành động, bạn có thể lệnh bạn chấp hành 1 quân lệnh, nếu chấp hành, bạn xem như sử dụng 1 [Sát]; nếu không chấp hành, bạn kết thúc giai đoạn hành động.",
	["zhuke"] = "Trúc Khoa",
	[":zhuke"] = "Chủ tướng kỹ, giảm 0.5 máu gốc, sau khi bạn chọn chấp hành quân lệnh, bạn có thể chọn lại quân lệnh để chấp hành. Khi bạn tiến vào trạng thái xích hoặc trạng thái chồng tướng, bạn có thể lệnh 1 người cùng thế lực hồi 1 máu.",
	["quanjia"] = "Khuyến Giá",
	[":quanjia"] = "Phó tướng kỹ, sau khi bạn mở tướng này lần đầu tiên, thực hiện triệu hoán thế lực; người mở tướng bởi kỹ năng này không trở thành dã tâm, người cùng thế lực với bạn rút 1 lá, người có kỹ năng \"Nhân Đức\" nhận kỹ năng \"Chương Vũ\" và \"Thụ Việt\"",

	["@jinwu-slash"] = "Căng Võ: Chọn 1 mục tiêu cho [Sát]",
	["zhuke-invoke"] = "Có thể phát động \"Trúc Khoa\" lệnh 1 người hồi 1 máu.",
	["@zhuke-select"] = "Trúc Khoa: Chọn 1 quân lệnh bạn muốn chấp hành.",
	
    ["#maxiumatie"] = "Tru Gian Nghĩa Tồn",
    ["maxiumatie"] = "Mã Hưu & Mã Thiết",
    ["&maxiumatie"] = "Mã Hưu Mã Thiết",
    ["illustrator:maxiumatie"] = "alien",
    --["designer:maxiumatie"] = "",
    ["mashu_maxiumatie"] = "Mã Thuật",
    ["kenshang"] = "Khẩn Thương",
    [":kenshang"] = "Bạn có thể sử dụng tùy ý số lá của bạn như [Sát] (ít nhất 1 lá); nếu làm vậy:\n * Khi đã chọn mục tiêu, bạn có thể lệnh tất cả người chơi ngoài tầm đánh của bạn trở thành mục tiêu của [Sát] này (bỏ qua hạn chế khoảng cách), hủy bỏ tất cả mục tiêu trong tầm đánh của bạn.\n * Sau khi lá [Sát] này kết toán, nếu số lá bạn đã đem sử dụng > X, bạn rút X lá; Ngược lại, bạn mất \"Mã Thuật\" hoặc kỹ năng này. (X là tổng số sát thương mà [Sát] này đã gây ra)",
    ["_kenshang:prompt"] = "Khẩn Thương: Có thể thay đổi mục tiêu thành tất cả người ngoài tầm đánh",
    ["@kenshang-choose"] = "Khấn Thương: Chọn 1 kỹ năng để mất đi",
    ["#KenshangTarget"] = "%from thay đổi mục tiêu của [Sát] thành %to ",

	["#fengxi"] = "Đông Ngô Tô Võ",
    ["fengxi"] = "Phùng Hy",
    ["yusui"] = "Ngọc Toái",
    [":yusui"] = "Một lần trong lượt của mỗi người, sau khi bạn trở thành mục tiêu của bài đen do người không cùng thế lực sử dụng, bạn có thể mất 1 máu rồi chọn:\n1. Lệnh họ bỏ X lá trên tay (X là giới hạn máu của họ); 2, Lệnh họ mất máu đến khi bằng với máu của bạn.",
    ["boyan"] = "Bác Ngôn",
    [":boyan"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người khác, họ bổ sung bài trên tay đến giới hạn máu của họ, trong lượt này họ không thể sử dụng hoặc đánh ra bài trên tay của họ; bạn có thể lệnh họ nhận kỹ năng \"Bác Ngôn (Tung Hoành)\" (Bỏ mô tả 'họ bổ sung bài trên tay đến giới hạn máu của họ') cho đến khi kết thúc lượt chơi tiếp theo của họ.",
    ["@yusui-choice"] = "Ngọc Toái: lựa chọn hành động cho %dest chấp hành",
    ["yusui:losehp"] = "Mất máu đến khi số máu bằng bạn.",
    ["yusui:discard"] = "Bỏ số bài trên tay bằng giới hạn máu.",
	["@boyan-zongheng"] = "Có thể lệnh cho %dest nhận kỹ năng \"Bác Ngôn (Tung Hoành)\"?",

	["boyanzongheng"] = "Bác Ngôn",
	[":boyanzongheng"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người khác, lệnh họ trong lượt này không thể sử dụng hoặc đánh ra bài trên tay của họ.",
	
	["#dengzhi"] = "Tuyệt Cảnh Ngoại Giao Gia",
	["dengzhi"] = "Đặng Chi",

	["jianliang"] = "Giản Lượng",
	[":jianliang"] = "Đầu giai đoạn rút bài, nếu bạn là người có ít bài trên tay nhất, bạn có thể lệnh người cùng thế lực bạn lần lượt rút 1 lá.",
	["weimeng"] = "Ngụy Minh",
	[":weimeng"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người khác có bài trên tay, bạn thu lấy tối đa X lá trên tay của họ (X là số máu của bạn), sau đó giao lượng bài tương đương cho họ. Bạn có thể lệnh họ nhận kỹ năng \"Ngụy Minh (Tung Hoành)\" (Thay mô tả X thành 1) cho đến khi kết thúc lượt tiếp theo của họ.",

	["weimengzongheng"] = "Ngụy Minh",
	[":weimengzongheng"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người khác có bài trên tay, bạn thu lấy 1 lá trên tay của họ, sau đó giao 1 lá cho họ.",



	["@weimeng-num"] = "Ngụy Minh: Chọn số lượng bài sẽ lấy từ %dest",

	["@weimeng-give"] = "Ngụy Minh: Chọn %arg lá giao cho %dest",

	["@weimeng-zongheng"] = "Có thể lệnh cho %dest nhận kỹ năng \"Ngụy Minh (Tung Hoành)\"?",
	
	["#xunchen"] = "Tam Công Mưu Chủ",
    ["xunchen"] = "Tuân Kham",
    ["fenglve"] = "Phong Lược",
    [":fenglve"] = "Một lần trong giai đoạn hành động, bạn có thể đấu điểm với 1 người khác. Nếu thắng, họ giao 2 lá trong vùng chơi của họ cho bạn; nếu thua, bạn giao 1 lá cho họ. Bạn có thể lệnh họ nhận kỹ năng \"Phong Lược (Tung Hoành)\" cho đến khi kết thúc lượt tiếp theo của họ.",
    ["anyong"] = "Ám Dũng",
    [":anyong"] = "Một lần trong lượt của mỗi người, khi 1 người cùng thế lực với bạn gây sát thương cho 1 người khác ngoài họ, có thể lệnh cho sát thương này gấp đôi; sau đó, nếu người nhận sát thương đã mở tất cả tướng, bạn tự mất 1 máu và mất kỹ năng này; nếu chỉ mở 1 tướng, bạn bỏ 2 lá trên tay.",
    ["@fenglve-give1"] = "Phong Lược: Chọn 1 lá giao cho %dest",
    ["@anyong-discard"] = "Ám Dũng: Bỏ 2 lá trên tay",
	
	["fenglvezongheng"] = "Phong Lược",
	[":fenglvezongheng"] = "Một lần trong giai đoạn hành động, bạn có thể đấu điểm với 1 người khác. Nếu thắng, họ giao 1 lá trong vùng chơi của họ cho bạn; nếu thua, bạn giao 1 lá cho họ.",
	["@fenglve-give2"] = "Phong Lược: Chọn 2 lá giao cho %dest",

	["@fenglve-zongheng"] = "Có thể lệnh cho %dest nhận kỹ năng \"Phong Lược (Tung Hoành)\"?",
	
	    
    ["#yanghu"] = "Chế Hoành Đồng Quỹ",
    ["yanghu"] = "Dương Hỗ",
    ["deshao"] = "Đức Thiệu",
    [":deshao"] = "X lần trong lượt của mỗi người (X là số máu của bạn), sau khi bạn trở thành mục tiêu duy nhất của bài đen do người khác sử dụng, nếu họ đã mở số tướng không nhiều hơn bạn, bạn có thể bỏ 1 lá của họ.",
    ["mingfa"] = "Minh Phạt",
    [":mingfa"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người khác thế lực; Khi kết thúc lượt tiếp theo của họ, nếu số bài trên tay họ ít hơn bạn, bạn gây 1 sát thương cho họ và thu lấy 1 lá trên tay họ; nếu bài trên tay họ nhiều hơn bạn, bạn bổ xung bài trên tay đến khi bằng họ, tối đa rút thêm 5 lá.",

    --["mingfazongheng"] = "Minh Phạt",
    --[":mingfazongheng"] = "Một lần trong giai đoạn hành động, bạn có thể bỏ 1 lá và chọn 1 người khác thế lực, bạn có thể lệnh họ nhận lấy \"Kì Chiến (Tung Hoành)\" cho đến khi kết thúc lượt tiếp theo của họ; Khi kết thúc lượt tiếp theo của họ, nếu số bài trên tay họ nhỏ hơn bạn, bạn gây 1 sát thương cho họ và thu lấy 1 lá trên tay họ.",

    --["@mingfa-zongheng"] = "Có thể lệnh cho %dest nhận \"Minh Phạt (Tung Hoành)",

    ["#MingfaEffect"] = "%arg của %from có hiệu lực",
	
	["newsgs"] = "Thập Chu Niên",
    
    
 	["#jianggan"] = "Phong Đích Huyền Tín",
	["jianggan"] = "Tưởng Cán",
	["weicheng"] = "Ngụy Thành",
	[":weicheng"] = "Khi bài trên tay bạn chuyển đến tay người chơi khác, nếu bài trên tay bạn ít hơn số máu hiện tại, có thể rút 1 lá.",
	["daoshu"] = "Đạo Thư",
	[":daoshu"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 chất và 1 người chơi có bài trên tay, thu lấy 1 lá bài trên tay người đó và so sánh với chất bài đã đoán;\nNếu trùng: bạn gây 1 sát thương cho họ và tăng thêm 1 lần sử dụng kỹ năng trong giai đoạn này;\nKhông trùng: bạn giao 1 lá bài trên tay có chất khác với lá bạn nhận cho họ, nếu không thể, mở toàn bộ bài trên tay.",
	["@daoshu-give"] = "Đạo Thư: chọn 1 lá và giao cho %dest",
    
    
    
    ["#zhouyi"] = "Điện Tinh Vũ Đại",
    ["zhouyi"] = "Chu Di",
    ["zhukou"] = "Trục Khấu",
    [":zhukou"] = "Trong lượt của mỗi người chơi, sau khi bạn gây sát thương lần đầu tiên trong giai đoạn hành động của họ, bạn có thể rút X lá (X là số lá bạn đã sử dụng trong lượt này, tối đa 5).",
    ["duannian"] = "Đoạn Niệm",
    [":duannian"] = "Kết thúc giai đoạn hành động, nếu bạn có bài trên tay, có thể bỏ đi tất cả bài trên tay, sau đó bổ xung bài đến giới hạn máu.",
    ["lianyou"] = "Liên Hựu",
    [":lianyou"] = "Khi bạn trận vong, có thể lệnh cho 1 người khác nhận kỹ năng \"Hưng Hỏa\"",
    ["xinghuo"] = "Hưng Hỏa",
    [":xinghuo"] = "Tỏa định kỹ, khi bạn gây sát thương Hỏa, sát thương này +1.",
    
    ["@lianyou"] = "Có thể phát động \"Liên Hữu\", chọn 1 người nhận \"Hưng Hỏa\"",
    
    ["#nanhualaoxian"] = "Tiên Nhân Chỉ Lộ",
    ["nanhualaoxian"] = "Nam Hoa Lão Tiên",
    ["gongxiu"] = "Cộng Tu",
    [":gongxiu"] = "Giai đoạn rút bài, có thể rút ít đi 1 lá, sau đó lựa chọn tối đa X người (X là giới hạn máu của bạn), lệnh họ:\n1. Rút 1 lá.\n2. Bỏ 1 lá.\nKhông thể liên tiếp lựa chọn cùng 1 mục.",
    ["jinghe"] = "Kinh Hợp",
    [":jinghe"] = "Một lần trong gian đoạn hành động, bạn có thể mở tổi đa X lá trên tay (X là giới hạn máu của bạn) và chọn số người tương đương có tướng đã mở; mỗi người có thể chọn và nhận 1 kỹ năng trong danh sách kỹ năng được lấy ngẫu nhiên cho đến đầu lượt tiếp theo của bạn.",
    ["leiji_tianshu"] = "Lôi Kích",
    [":leiji_tianshu"] = "Khi bạn sử dụng/đánh ra [Thiểm], bạn có thể lệnh 1 người khác tiến hành phán xét, nếu kết quả là chất Bích, bạn gây 2 sát thương Lôi cho họ.",
    ["yinbing"] = "Âm Binh",
    [":yinbing"] = "Tỏa định kỹ, khi bắt đầu kết toán hiệu quả của [Sát] gây sát thương do bạn sử dụng, sửa hiệu quả thành mục tiêu mất X máu (X là số sát thương). Sau khi người khác mất máu, bạn rút 1 lá.",
    ["huoqi"] = "Hoạt Khí",
    [":huoqi"] = "Một lần trong giai đoạn hành động, bạn có thể bỏ 1 lá và chọn 1 người có ít máu nhất, lệnh họ hồi 1 máu và rút 1 lá.",
    ["guizhu"] = "Quỷ trợ",
    [":guizhu"] = "Một lần mỗi lượt, khi 1 người tiến vào trạng thái hấp hối, bạn có thể rút 2 lá.",
    ["xianshou"] = "Tiên Thụ",
    [":xianshou"] = "Một lần trong giai đoạn hành động, bạn có thể chọn 1 người, lệnh họ rút 1 lá; Nếu họ không bị thương, họ rút thêm 1 lá.",
    ["lundao"] = "Luận Đạo",
    [":lundao"] = "Sau khi nhận sát thương, nếu số bài trên tay nguồn sát thương nhiều hơn bạn, có thể bỏ 1 lá của họ; nếu ít hơn, bạn có thể rút 1 lá.",
    ["guanyue"] = "Quan Nguyệt",
    [":guanyue"] = "Giai đoạn kết thúc, bạn có thể xem 2 lá trên cùng chồng bài, thu lấy 1 lá trong số đó, đặt lá còn lại lên đầu chồng bài.",
    ["yanzheng"] = "Ngôn Chính",
    [":yanzheng"] = "Giai đoạn chuẩn bị, nếu số bài trên tay bạn nhiều hơn 1, bạn có thể giữ lại 1 lá và bỏ đi số lá còn lại và chọn tối đa X người (X là số lá đã bỏ), bạn gây 1 sát thương cho họ.",

    ["@gongxiu-choose"] = "Cộng Tu: Lựa chọn 1 hiệu quả",
    ["gongxiu_choose:draw"] = "Rút 1 lá",
    ["gongxiu_choose:discard"] = "Bỏ 1 lá",
    ["@gongxiu-draw"] = "Cộng Tu: chọn tối đa %arg người rút 1 lá.",
    ["@gongxiu-discard"] = "Cộng Tu: chọn tối đa %arg người bỏ 1 lá.",
    ["@gongxiu-throw"] = "Cộng Tu: Chọn 1 lá để bỏ.",
    
    ["@jinghe-choose"] = "Kinh Hợp: Chọn 1 kỹ năng cho bản thân.",
    
    ["@yanzheng"] = "Có thể phát động \"Ngôn Chính\", chọn 1 lá trên tay và bỏ đi những lá còn lại.",
    ["@yanzheng-damage"] = "Ngôn Chính: chọn tối đa %arg người nhận 1 sát thương.",
	
	["#lvlingqi"] = "Vô Song Hao Cơ",
    ["lvlingqi"] = "Lữ Linh Khởi",
    ["guowu"] = "Quắc Vũ",
    [":guowu"] = "Đầu giai đoạn hành động, bạn có thể mở tất cả bài trên tay, căn cứ vào số loại bài bạn có mà bạn nhận hiệu quả tương ứng:\n  1+: Bạn thu lấy 1 lá [Sát] từ chồng bài bỏ.\n  2+: Trong giai đoạn này, bạn sử dụng bài không hạn chế khoảng cách.\n  3: Một lần trong giai đoạn này, khi bạn sử dụng [Sát], có thể chỉ định thêm tối đa 2 mục tiêu.",
    ["zhuangrong"] = "Trang Nhung",
    [":zhuangrong"] = "Một lần trong giai đoạn hành động, bạn có thể bỏ 1 lá công cụ, thu lấy kỹ năng \"Vô Song\" đến hết giai đoạn này.",
    ["wushuang_lvlingqi"] = "Vô Song",
    ["shenwei"] = "Thần Uy",
    [":shenwei"] = "Chủ tướng kỹ, Tỏa định kỹ, giảm 0.5 máu gốc; Giới hạn trữ bài trên tay bạn +2; Giai đoạn rút bài, nếu bạn là người có số máu lớn nhất, số lá bạn rút +2.",
    ["@guowu-add"] = "Có thể phát động \"Quắc Vũ\", thêm 2 mục tiêu cho [%arg] đang sử dụng.",
    
    ["$AddCardTarget"] = "%from đã phát động \"%arg\", thêm mục tiêu %to cho %card",
    ["$RemoveCardTarget"] = "%from đã phát động \"%arg\", bớt mục tiêu %to cho %card",
	
	["#yangwan"] = "Dung Mạt Chi Ly",
    ["yangwan"] = "Dương Uyển",
    --["designer:yangwan"] = "",
    ["youyan"] = "Dụ Ngôn",
    [":youyan"] = "Một lần trong lượt của bạn, sau khi bài của bạn tiến vào chồng bài bỏ do bỏ bài, bạn có thể mở 4 lá trên đầu chồng bài và thu lấy những lá khác chất với những lá bạn đã bỏ trong lần này.",
    ["zhuihuan"] = "Truy Hoàn",
    [":zhuihuan"] = "Khi kết thúc lượt, bạn có thể chọn tối đa 2 người, lệnh mỗi người nhận 1 tiêu ký [Truy Hoàn] khác nhau (Người chơi không được biết loại tiêu ký [Truy Hoàn] đã nhận). Đến khi bắt đầu lượt tiếp theo của bạn, sau khi họ nhận sát thương, họ bỏ đi tiêu ký [Truy Hoàn]; sau đó, nếu [Truy Hoàn] đã bỏ là:\n* \"Sát thương\": Họ gây 1 sát thương cho nguồn sát thương;\n* \"Bỏ bài\": Nguồn sát thương bỏ 2 lá trên tay.",

    ["@zhuihuan-invoke"] = "Có thể phát động \"Truy Hoàn\", chọn tối đa 2 người",
    ["@zhuihuan-choose"] = "Truy Hoàn: Chọn loại [Truy Hoàn] cho %dest",

    ["#ZhuihuanEffect"] = "%arg của %from đã có hiệu quả với %to",
	
	["zhuihuan:damage"] = "Truy Hoàn - Sát thương",
	["zhuihuan:discard"] = "Truy Hoàn - Bỏ bài",
	
	["lifeng"] = "Lý Phong",
	["#lifeng"] = "Kế Phụ Tận Sự",
	["illustrator:lifeng"] = "biou09",
    ["food"] = "Lương",
	["@tunchu-push"] = "Truẫn Trữ: Chọn từ 1 đến 2 lá để đặt [Lương]",
	["tunchu"] = "Truân Trữ",
	[":tunchu"] = "Giai đoạn rút bài, bạn có thể rút thêm 2 lá; nếu làm vậy, bạn không thể sử dụng [Sát] trong lượt này; sau đó, khi kết thúc giai đoạn rút bài, bạn đặt từ 1 đến 2 lá trên tay lên tướng này, gọi là [Lương]." ,
	["shuliang"] = "Thâu Lương",
	["@shuliang"] = "Có thể bỏ 1 [Lương] để cho %src rút 2 lá.",
	[":shuliang"] = "Giai đoạn kết thúc của 1 người cùng thế lực với bạn, nếu khoảng cách từ bạn đến họ không lớn hơn số [Lương], bạn có thể đưa 1 [Lương] vào chồng bài bỏ, lệnh họ rút 2 lá.",
	
	["$tunchu1"] = "Chỉ có lo tích trữ lương thảo thì mới đủ sức đối đầu",
	["$tunchu2"] = "Tích cóp nhằm an định xã tắc, cất trữ phòng lúc cần đến",
	["$shuliang1"] = "Kế thừa ý chí cha ông, trợ Thừa tướng tái phạt Trung Nguyên",
	["$shuliang2"] = "Binh mã chưa xuất vội, lo chuẩn bị lương thảo trước đã!",
	["~lifeng"] = "Ngựa đói người mệt, quân ta thế lá xong......",
	
		
    ["lingcao"] = "Lăng Tháo",
	["#lingcao"] = "Kích Lưu Dũng Tiến",
	["illustrator:lingcao"] = "YanBai",
	["dujin"] = "Độc Tiến",
	[":dujin"] = "Giai đoạn rút bài, bạn có thể rút thêm X lá (X là 1 nửa số lá trong vùng trang bị của bạn, làm tròn lên). Sau khi bạn mở tướng này lần đầu, nếu không có người nào khác cùng thế lực với bạn (bao gồm cả người đã trận vong), bạn nhận 1 tiêu ký [Tiên Khu]" ,
	
	["$dujin1"] = "Đem quân hơn mười vạn, còn không bằng cho ta thêm một giáp!",
	["$dujin2"] = "Thuyền nhỏ độc tiến, phá địch tiên phong!",
	["~lingcao"] = "Aaaa~ Tên ở đâu ra thế này......",

	
	["lord_ex"] = "Bất Thần",
	["lord_ex_card"] = "Bất Thần",
	
	
	["#mengda"] = "Đãi Quân Phản Phúc",
	["mengda"] = "Mạnh Đạt",
	["qiuan"] = "Cầu An",
	[":qiuan"] = "Khi bạn nhận sát thương, nếu bạn không có [Hàm], có thể đem lá gây sát thương cho bạn đặt lên tướng này, gọi là [Hàm], sau đó chặn sát thương này.",
	["liangfan"] = "Lượng Phản",
	[":liangfan"] = "Tỏa định kỹ, Giai đoạn chuẩn bị, nếu bạn có [Hàm], bạn mất 1 máu, sau đó thu lấy [Hàm]; Trong lượt này, sau khi bạn gây sát thương cho 1 người do sử dụng [Hàm], bạn có thể thu lấy 1 lá của họ.",
	["letter"] = "Hàm",

	["#LiangfanEffect"] = "%from đã sử dụng [%arg] để gây sát thương và thu lấy 1 lá của %to",
	
	["@liangfan"] = "Lượng Phản: Lấy 1 lá của %dest",
	
	
	["#tangzi"] = "Đắc Thì Thức Phong",
	["tangzi"] = "Đường Tư",
	["xingzhao"] = "Hưng Thạo",
	[":xingzhao"] = "Tỏa định kỹ, dựa theo số thế lực trên bàn chơi có người bị thương: \n1 trở lên: Bạn nhận \"Tuân Tuân\".\n2 trở lên: Sau khi nhận sát thương, giữa bạn và nguồn gây sát thương, người ít bài trên tay hơn rút 1 lá.\n3 trở lên: Đầu giai đoạn bỏ bài, giới hạn trữ bài của bạn +4.\n4 trở lên: Khi bạn mất bài trong vùng trang bị, rút 1 lá.",
	["xunxun_tangzi"] = "Tuân Tuân",
	
	["#zhanglu"] = "Chính Khoan Giáo Huệ",
	["zhanglu"] = "Trương Lỗ",
	["bushi"] = "Bố Thí",
	[":bushi"] = "Trước khi kết thúc lượt, bạn nhận X [Nghĩa Xá] (X là số máu của bạn). Đầu giai đoạn chuân bị của người khác, nếu bạn có [Nghĩa Xá], bạn có thể giao 1 lá cho họ, sau đó bạn bỏ 1 [Nghĩa Xá] và rút 2 lá. Đầu giai đoạn chuẩn bị, bạn bỏ X lá (X là số người chơi còn sống trừ số máu của bạn và trừ 2), sau đó bỏ tất cả [Nghĩa Xá]",
	["midao"] = "Mễ Đạo",
	[":midao"] = "Đầu giai đoạn kết thúc, nếu không có [Mễ], bạn có thể rút 2 lá, sau đó bạn đặt 2 lá lên tướng này, gọi là [Mễ]. Trước khi 1 kết quả phán xét có hiệu lực, bạn có thể đánh ra 1 lá [Mễ] để thay đổi kết quả phán xét, sau đó thu lấy lá phán xét ban đầu.",
    ["bushi:discard"] = "Có thể phát động \"Bố Thí\" để bỏ %arg lá",
    ["bushi:mark"] = "Có thể phát động \"Bố Thí\" để nhận [Nghĩa Xá]",
    ["yishe"] = "Nghĩa Xá",
    ["@bushi-give"] = "Có thể phát động \"Nghĩa Xá\" để giao 1 lá cho %src",
    ["rice"] = "Mễ",
    ["@midao-push"] = "Mễ Đạo: Chọn 2 lá để đặt [Mễ]",
    ["@midao-card"] = CommonTranslationTable["@askforretrial"],
	
	["#mifangfushiren"] = "Trục Giá Nghênh Trần",
	["mifangfushiren"] = "Mi Phương & Phó Sĩ Nhân",
	["&mifangfushiren"] = "Mi Phương Phó Sĩ Nhân",
	["fengshix"] = "Phong Thế",

	[":fengshix"] = "Sau khi bạn sử dụng bài chỉ định 1 mục tiêu duy nhất, nếu số bài trên tay họ nhỏ hơn bạn, bạn có thể bỏ 1 lá của bạn và họ, sau đó sát thương này +1. Sau khi bạn trở thành mục tiêu duy nhất của bài từ người khác, nếu số lá trên tay bạn nhỏ hơn họ, họ có thể lệnh bạn bỏ 1 lá của bạn và họ, sau đó sát thương này +1.",
	
	["@fengshix"] = "Có thể phát động \"Phong Thế\" của %src",
	
	
	["#liuqi"] = "Cư Ngoại Nhi An",
	["liuqi"] = "Lưu Kỳ",
	["wenji"] = "Vấn Kế",
	[":wenji"] = "Đầu giai đoạn hành động, bạn có thể lệnh 1 người khác giao cho bạn 1 lá ngửa mặt. Nếu họ cùng thế lực hoặc vô thế lực, lượt này bạn sử dụng lá này không hạn chế khoảng cách cùng số lần và không thể hưởng ứng; Nếu họ không cùng thế lực, bạn giao cho họ 1 lá bài khác.",
	
	["tunjiang"] = "Truân Giang",
	[":tunjiang"] = "Giai đoạn kết thúc, nếu bạn trong giai đoạn hành động sử dụng ít nhất 1 lá và không chỉ định người khác làm mục tiêu, bạn có thể rút X lá (X là số thế lực trên bàn chơi).",
	["@wenji"] = "Có thể kích \"Vấn Kế\", chọn 1 người khác",
	["@wenji-give"] = "Vấn Kế, chọn 1 lá và giao cho %src",
	["#WenjiEffect"] = "%from đã phát động %arg, [%arg2] không thể bị phản ứng.",
	["#wenji-effect"] = "Vấn Kế",
	
	["#shixie"] = "Bách Việt Linh Y",
	["shixie"] = "Sĩ Nhiếp",
	["biluan"] = "Tị Loạn",
	[":biluan"] = "Tỏa định kỹ, khoảng cách từ người khác tới bạn +X (X là số lá trong vùng trang bị của bạn)",
	["lixia"] = "Lễ Hạ",
	[":lixia"] = "Tỏa định kỹ, Giai đoạn chuẩn bị của người khác thế lực, nếu bạn không ở trong tầm đánh của họ, bạn lệnh họ chọn:\n1. Lệnh bạn rút 1 lá;\n2. Bỏ 1 lá trong vùng trang bị của bạn, sau đó họ mất 1 máu.",

    ["@lixia-choose"] = "Lễ Hạ: Chọn lệnh %src rút 1 lá hoặc bỏ 1 lá trong vùng trang bị của %src và mất 1 máu",
    ["lixia:draw"] = "Rút bài",
    ["lixia:discard"] = "Bỏ trang bị",

    ["#zhonghui"] = "Kiệt Ngạo Đích Dã Tâm Gia",
    ["zhonghui"] = "Chung Hội",
    ["quanji"] = "Quyền Kế",
    [":quanji"] = "Một lần trong lượt ứng với mỗi thời điểm, sau khi bạn gây hoặc nhận sát thương, bạn có thể rút 1 lá, sau đó đặt ngửa 1 lá lên tướng, gọi là [Quyền]. Giới hạn trữ bài của bạn +X (X là số [Quyền]).",
    ["paiyi"] = "Bài Dị",
    [":paiyi"] = "Một lần trong giai đoạn hành động, có thể đưa 1 [Quyền] vào chồng bài bỏ và chọn 1 người, họ rút X lá (X là số [Quyền] bạn có, tối đa 7); sau đó nếu số bài trên tay họ lớn hơn bạn, bạn gây 1 sát thương cho họ.",

    ["@quanji-push"] = "Quyền Kế: Đặt 1 lá lên tướng làm [Quyền]",
    ["power_pile"] = "Quyền",


    ["#dongzhao"] = "Di Tôn Dị Đỉnh",
    ["dongzhao"] = "Đổng Chiêu",
    ["quanjin"] = "Khuyến Tiến",
    [":quanjin"] = "Một lần trong giai đoạn hành động, bạn có thể giao 1 lá trên tay cho người từng nhận sát thương trong giai đoạn này và lệnh họ chấp hành 1 [Quân Lệnh]. Nếu họ chấp hành, bạn rút 1 lá; nếu không chấp hành và bạn không phải người có nhiều bài trên tay nhất, bạn bổ xung bài trên tay đến khi bằng người có nhiều bài trên tay nhất, tối đa 5 lá.",
    ["zaoyun"] = "Tạc Vận",
    [":zaoyun"] = "Một lần trong giai đoạn hành động, có thể chọn 1 người không cùng thế lực với bạn và khoảng cách từ bạn đến họ lớn hơn 1 và bỏ X lá bài trên tay (X là khoảng cách từ bạn đến họ -1), khoảng cách từ bạn đến họ là 1 cho đến hết lượt, bạn gây 1 sát thương cho họ.",

    ["#xushu"] = "Nan Vi Hoàn Thần",
    ["xushu"] = "Từ Thứ",
    ["qiance"] = "Khiêm Sách",
	[":qiance"] = "Sau khi người cùng thế lực với bạn xác định mục tiêu cho lá công cụ, họ có thể lệnh những mục tiêu thuộc Đại thế lực không thể hướng ứng với lá này",
	["jujian"] = "Cử Tiến",
	[":jujian"] = "Phó tướng kỹ, giảm 0.5 máu gốc, khi 1 người cùng thế lực với bạn tiến vào trạng thái hấp hối, bạn có thể lệnh họ hồi đến 1 máu, sau đó bạn đổi Phó tướng",
	["@qiance"] = "Có thể phát động \"Khiêm Sách\" của %src",
    
    ["#wujing"] = "Hàn Mã Lưu Kim",
    ["wujing"] = "Ngô Cảnh",
    ["diaogui"] = "Điều Quy",
    [":diaogui"] = "Một lần trong giai đoạn hành động, có thể sử dụng 1 lá trang bị như [Điệu Hổ Ly Sơn]; Sau đó, nếu bằng cách này thế lực của bạn có sự thay đổi về đội hình, bạn rút X lá (X là số người của đội hình đông nhất trong những quan hệ đội hình ở thế lực của bạn có sự thay đổi).",
    ["fengyang"] = "Phong Dương",
    [":fengyang"] = "Trận pháp kỹ, người không cùng thế lực với bạn không thể thu lấy hoặc bỏ trang bị của người cùng đội hình với bạn.",

    ["#yanbaihu"] = "Sài Nha Lạc Giản",
    ["yanbaihu"] = "Nghiêm Bạch Hổ",
    ["zhidao"] = "Trĩ Đạo",
    [":zhidao"] = "Tỏa định kỹ, đầu giai đoạn hành động, bạn chọn 1 người khác; trong lượt này, khoảng cách từ bạn đến họ là 1, bạn không thể chọn người ngoài bạn và họ làm mục tiêu của bài; sau khi bạn gây sát thương cho họ lần đầu tiên trong giai đoạn này, bạn thu lấy 1 lá trong vùng chơi của họ.",
    ["jilix"] = "Ký Li",
    [":jilix"] = "Tỏa định kỹ, sau khi kết toán xong lá cơ bản Đỏ hoặc công cụ phổ thông Đỏ, nếu bạn là mục tiêu duy nhất của lá này, bạn lệnh cho người sử dụng xem như sử dụng lá cùng tên với lá đó với bạn (không giới hạn khoảng cách, số lần sử dụng); khi bạn nhận sát thương lần thứ 2 trong cùng 1 giai đoạn, bạn chặn sát thương và loại bỏ tướng này.",
    
    ["#zhidao-damage"] = "Trĩ Đạo",
    ["@zhidao-target"] = "Trĩ Đạo: Chọn 1 người khác",
    ["#ZhidaoEffect"] = "%from đã phát động \"%arg\", nhận 1 lá trong vùng chơi của %to",
    
    ["jilix:target"] = "Có thể phát động \"Ký Li\", lệnh %src 1 lần nữa xem như sử dụng [%arg] với bạn.",
    ["jilix:damage"] = "Có thể phát động \"Ký Li\", chặn sát thương và loại bỏ tướng này.",

    ["ImperialEdict"] = "Chiếu Thư",
    [":ImperialEdict"] = "Bài Trang bị - Bảo vật\n\nKỹ năng:\n" ..
                    "* Sau khi sử dụng lá này, bạn đặt lá này vào vùng tướng của bạn.\n" ..
					"* Một lần trong giai đoạn hành động của người có cùng thế lực với bạn, nếu họ thuộc tiểu thế lực, có thể đặt tối đa 2 lá trên tay lên tướng của bạn; nếu không thuộc tiểu thế lực, họ có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Chiếu].\n" ..
                    "* Một lần trong giai đoạn hành động, nếu có 4 [Chiếu] không cùng chất, bạn có thể đưa tất cả [Chiếu] vào chồng bài bỏ, rút ngẫu nhiêu 1 lá công cụ thế lực.\n" ,

    ["imperialedictattach"] = "Đặt bài trên tay",
    [":imperialedictattach"] = "Một lần trong giai đoạn hành động của người có cùng thế lực với bạn, nếu họ thuộc tiểu thế lực, có thể đặt tối đa 2 lá trên tay lên tướng của bạn; nếu không thuộc tiểu thế lực, họ có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Chiếu].",
    ["imperialedicttrick"] = "Nhận bài công cụ",
    [":imperialedicttrick"] = "Một lần trong giai đoạn hành động, nếu có 4 lá [Chiếu] không cùng chất, bạn có thể đưa tất cả [Chiếu] vào chồng bài bỏ, rút ngẫu nhiêu 1 lá công cụ thế lực.",

    ["rule_the_world"] = "Hiệu Lệnh Thiên Hạ",
    [":rule_the_world"] = "Bài công cụ - Ngụy\n\nSử dụng: Trong giai đoạn hành động.\nMục tiêu: Một người không phải ít máu nhất.\nHiệu quả: Ngoại trừ mục tiêu, mỗi người có thể lựa chọn:\n1. Bỏ 1 lá trên tay xem như sử dụng [Sát] không giới hạn tầm với mục tiêu; người thế lực Ngụy không cần bỏ bài.\n2. Bỏ 1 lá của mục tiêu, người thế lực Ngụy thu lấy lá đó.",
    ["rule_the_world:slash"] = "%log xem như sử dụng [Sát] với %to",
    ["rule_the_world:discard"] = "Một lá bài của %to bị %log",
    ["rule_the_world_slash"] = "Bỏ 1 lá bài và",
    ["rule_the_world_discard"] = "bỏ đi",
    ["rule_the_world_getcard"] = "thu lấy",
    ["@rule_the_world-slash"] = "Hiệu Lệnh Thiên Hạ: Bỏ 1 lá trên tay, xem như sử dụng [Sát] với %dest.",

    ["conquering"] = "Khắc Phục Trung Nguyên",
    [":conquering"] = "Bài công cụ - Thục\n\nSử dụng: Trong giai đoạn hành động.\nMục tiêu: Tùy ý người chơi.\nHiệu quả: Họ lựa chọn 1 mục:\n1. Xem như sử dụng [Sát], khi người thế lực Thục gây sát thương do sử dụng [Sát] này, sát thương +1.\nRút 1 lá, người thế lực Thục đổi thành rút 2 lá.",
    ["@conquering-slash"] = "Khắc Phục Trung Nguyên: Chọn mục tiêu, xem như sử dụng [Sát], hoặc bấm \"Hủy bỏ\" để rút bài. ",

    ["consolidate_country"] = "Cố Quốc An Bang",
    [":consolidate_country"] = "Bài công cụ - Ngô\n\nSử dụng: Trong giai đoạn hành động.\nMục tiêu: Bản thân.\nHiệu quả: Bạn rút 8 lá sau đó bỏ ít nhất 6 lá trên tay, nếu bạn thuộc thế lực Ngô, có thể giao tùy ý tối đa 6 lá cho người khác thuộc thế lực Ngô, mỗi người tối đa 2 lá.",

    ["@consolidate_country-discard"] = "Cố Quốc An Bang: Chọn tối thiểu 6 lá trên tay để bỏ",
    ["@consolidate_country-give"] = "Cố Quốc An Bang: Có thể giao 6 lá cho người thế lực Ngô khác, tối đa 2 lá mỗi người.",

    ["chaos"] = "Văn Hòa Loạn Võ",
    [":chaos"] = "Bài công cụ - Quần\n\nSử dụng: Trong giai đoạn hành động.\nMục tiêu: Tất cả người chơi.\nHiệu quả: Mục tiêu mở bài trên tay, sau đó bạn chọn 1 mục:\n1. Lệnh họ bỏ 2 lá khác loại trên tay.\n2. Bỏ 1 lá trên tay họ.\nNgười thế lực Quần sau khi chấp hành lựa chọn của bạn, nếu họ không có bài trên tay, họ bổ sung bài trên tay tới máu hiện tại.",
    
    ["chaos:letdiscard"] = "Lệnh %to bỏ 2 lá không cùng loại trên tay",
    ["chaos:discard"] = "Bỏ 1 lá trên tay %to",

    ["@chaos-select"] = "Văn Hòa Loạn Võ: Chọn 2 lá không cùng loại trên tay để bỏ.",

    ["@trick-show"] = "Có thể mở 1 tướng để [%arg] có thêm hiệu ứng.",
    ["trick_show:show_head"] = "Mở chủ tướng",
    ["trick_show:show_deputy"] = "Mở phó tướng",

    ["#simazhao"] = "Trào Phong Khai Thiên",
    ["simazhao"] = "Tư Mã Chiêu",
    ["suzhi"] = "Túc Trí",
    [":suzhi"] = "Tỏa định kỹ:\nGiới hạn ba lần trong lượt của bạn đối với các mục sau:\n1. Khi bạn gây sát thương cho mục tiêu của [Sát] hoặc [Quyết Đấu], bạn lệnh số sát thương +1.\n 2. Khi bạn sử dụng công cụ không chuyển hóa, bạn rút 1 lá.\n 3. Sau khi bài của người khác tiến vào chồng bài bỏ do bỏ đi, bạn thu lấy 1 lá của họ.\nNếu chưa phát động \"Túc Trí\" 3 lần trong lượt:\n1. Bạn có thể sử dụng công cụ không chuyển hóa không hạn chế khoảng cách.\n2. Khi kết thúc lượt chơi, bạn nhận kỹ năng \"Phản Quỹ\" đến trước khi bắt đầu lượt tiếp theo của bạn.",
    ["zhaoxin"] = "Chiêu Tâm",
    [":zhaoxin"] = "Sau khi nhận sát thương, có thể mở tất cả bài trên tay, sau đó hoán đổi bài trên tay với 1 người khác không nhiều bài hơn bạn.",
    ["@zhaoxin-exchange"] = "Chiêu Tâm: Chọn 1 người có bài trên tay không nhiều hơn bạn để đổi bài.",
    ["fankui_simazhao"] = "Phản Quỹ",
    
    ["#xuyou"] = "Tất Phương Kiểu Dực",
    ["xuyou"] = "Hứa Du",

    ["chenglve"] = "Thành Lược",
    [":chenglve"] = "Sau khi kết toàn bài do 1 người cùng thế lực với bạn sử dụng, nếu số mục tiêu nhiều hơn 1, có thể lệnh họ rút 1 lá, sau đó nếu bạn đã nhận sát thương từ lá bài này, có thể lệnh 1 người cùng thế lực với bạn không có tướng úp và không có tiêu ký nào nhận được 1 tiêu ký [Âm Dương Ngư].",
    ["shicai"] = "Thị Tài",
    [":shicai"] = "Tỏa định kỹ, sau khi nhận sát thương, nếu sát thương này là 1, bạn rút 1 lá; nhiều hơn 1, bạn bỏ 2 lá.",

    ["@chenglve-mark"] = "Thành Lược: Chọn 1 người nhận tiêu ký [Âm Dương Ngư].",

    ["#xiahouba"] = "Cức Đồ Tráng Chí",
    ["xiahouba"] = "Hạ Hầu Bá",
    ["baolie"] = "Báo Liệt",
    [":baolie"] = "Tỏa định kỹ, Đầu giai đoạn hành động, lệnh những người không cùng thế lực có tầm đánh đến bạn sử dụng [Sát] với bạn, nếu không bạn bỏ 1 lá của họ; Bạn sử dụng [Sát] với người có máu không ít hơn bạn không giới hạn tầm đánh và số lần.",
    ["@baolie-slash"] = "Báo Liệt: Sử dụng [Sát] với %src, hoăc họ bỏ 1 lá của bạn.",

    ["#zhugeke"] = "Hưng Gia Xích Tộc",
    ["zhugeke"] = "Gia Cát Khác",
    ["aocai"] = "Ngạo Tài",
    [":aocai"] = "Ngoài lượt của bạn, khi bạn cần sử dụng hoặc đánh ra bài cơ bản, bạn có thể xem hai lá trên đầu chồng bài, có thể sử dụng hoặc đánh ra lá cơ bản có tên tương ứng trong đó.",
    ["duwu"] = "Độc Võ",
    [":duwu"] = "Hạn định kỹ, giai đoạn hành động, bạn có thể chọn tất cả người khác thế lực trong tầm đánh và lựa chọn [Quân Lệnh], họ lần lượt chọn có chấp hành [Quân Lệnh] hay không, nếu không chấp hành, bạn gây 1 sát thương cho họ và rút một lá; sau khi 1 người thoát khỏi trạng thái hấp hối do nhận sát thương từ kỹ năng này, bạn mất 1 máu.",
    
    ["#aocai"] = "Ngạo Tài",
    ["@aocai-view"] = "Ngạo Tài: Chọn 1 lá phù hợp để sử dụng/đánh ra",

    ["#sunchen"] = "Thực Tủy Đích Triêu Đường Khách",
    ["sunchen"] = "Tôn Lâm",
    ["shilu"] = "Thị Lực",
    [":shilu"] = "Khi có người trận vong, có thể đặt tất cả tướng của họ lên tướng này, gọi là [Lục], nếu họ bị bạn giết,bạn nhận 2 lá tướng thừa ngẫu nhiên đặt lên tướng này, gọi là [Lục]. Giai đoạn chuẩn bị, nếu bạn có [Lục], có thể bỏ tối đa X lá (X là số [Lục]) rồi rút số lá tương ứng.",
    ["xiongnve"] = "Hung Ngược",
    [":xiongnve"] = "Đầu giai đoạn hành động, có thể bỏ 1 [Lục], chọn 1 mục có hiệu quả trong lượt này:\n1. Khi bạn gây sát thương cho người cùng thế lực với [Lục] đã bỏ, sát thương này +1.\n2. Khi bạn gây sát thương cho người cùng thế lực với [Lục] đã bỏ, thu lấy 1 lá của họ.\n3. Bạn sử dụng bài với mục tiêu cùng thế lực với [Lục] đã bỏ không giới hạn số lần.\nKết thúc giai đoạn hành động, có thể bỏ 2 [Lục], trước khi lượt chơi tiếp theo của bạn bắt đầu, khi bạn nhận sát thương từ người khác, sát thương này -1. ",

    ["#xiongnve-effect"] = "Hung Ngược",

    ["massacre"] = "Lục",
    ["@shilu"] = "Thị Lục: có thể bỏ tối đa%arg lá rồi rút số lá tương ứng.",
    ["@xiongnve-continue"] = "Hung Ngược: Có thể tiếp tục bỏ [Lục]",
    
    ["#GetMassacreDetail"] = "%from đã nhận [Lục] %arg",
    ["#dropMassacreDetail"] = "%from đã bỏ [Lục] %arg",
    ["#GetMassacre"] = "%from đã nhận %arg [Lục]",
    
    ["@xiongnve-choice"] = "Hung Ngược: Lựa chọn 1 tác dụng.",
    ["xiongnve:adddamage"] = "+1 sát thương",
    ["xiongnve:extraction"] = "Lấy bài sau khi gây sát thương",
    ["xiongnve:nolimit"] = "Sử dụng bài không giới hạn số lần",
    
    ["#xiongnveAdddamage"] = "Lượt này, sát thương %from gây cho người thế lực %arg +1",
    ["#xiongnveExtraction"] = "Lượt này, %from lấy 1 lá của người thế lực %arg sau khi gây sát thương cho họ",
    ["#xiongnveNolimit"] = "Lượt này, %from sử dụng bài lên người thế lực %arg không giới hạn số lần.",
    ["xiongnve_avoid"] = "Hung Ngược: Giảm sát thương.",

	["xiongnve:attack"] = "Có thể phát động \"Hung Ngược\", bỏ 1 [Lục] để có hiệu quả tương ứng với thế lực đó",	
	["xiongnve:defence"] = "Có thể phát động \"Hung Ngược\", bỏ 2 [Lục] để lệnh sát thương nhận được -1",

    ["#panjun"] = "Quan Nhân Vu Vy",
    ["panjun"] = "Phan Tuấn",
    ["congcha"] = "Quan Vy",
    [":congcha"] = "Giai đoạn chuẩn bị, bạn có thể chọn 1 người không có thế lực; Trước khi bắt đầu lượt tiếp theo của bạn, khi họ mở tướng và trở thành có thế lực, nếu họ cùng thế lực với bạn, bạn và họ rút 2 lá; nếu không cùng thế lực, họ mất 1 máu. Giai đoạn rút bài, nếu không có người không có thế lực, bạn có thể lệnh số lá rút +2.",
    ["gongqing"] = "Công Thanh",
    [":gongqing"] = "Tỏa định kỹ, khi bạn nhận sát thương, nếu tầm đánh của nguồn sát thương lớn hơn 3, sát thương này +1; nếu tầm đánh của nguồn sát thương nhỏ hơn 3 và sát thương lớn hơn 1, sát thương này trở thành 1.",
    ["@congcha-target"] = "Có thể phát động \"Quan Vy\", chọn 1 người không có thế lực.",
    
    ["#congcha-effect"] = "Quan Vy",

    
    ["#wenqin"] = "Dương Châu Thích Sử",
    ["wenqin"] = "Văn Khâm",
    ["jinfa"] = "Căng Phạt",
    [":jinfa"] = "Một lần trong giai đoạn hành động, có thể bỏ 1 lá và chọn 1 người khác có bài, họ chọn:\n1. Lệnh bạn lấy 1 lá của họ.\n2. Đưa 1 trang bị cho bạn, nếu bạn nhận được lá ♠ và lá đó còn trên tay bạn, xem như họ sử dụng 1 [Sát] với bạn.",
    ["@jinfa-give"] = "Căng Phạt: Chọn 1 trang bị giao cho %src hoặc bấm hủy và lệnh %src lấy 1 lá của bạn.",


    ["#huangzu"] = "Giang Hạ Phúc Tâm",
    ["huangzu"] = "Hoàng Tổ",
    ["xishe"] = "Vãn Cung",
    [":xishe"] = "Giai đoạn chuẩn bị của người khác, bạn có thể bỏ 1 lá trong vùng trang bị và xem như sử dụng 1 [Sát] với họ không giới hạn khoảng cách, nếu số máu của họ nhỏ hơn của bạn, tất cả người chơi không thể hưởng ứng [Sát] này; bạn có thể lặp lại quá trình này. Khi lượt chơi kết thúc, nếu trong lượt họ trận vong và nguồn là [Sát] của bạn, bạn có thể đổi phó tướng, tướng sau khi đổi được úp xuống.",
    ["@xishe-slash"] = "Có thể phát động \"Văn Cung\", bỏ 1 lá trong vùng trang bị, xem như sử dụng [Sát] với %src",
    
    ["#xishe-transform"] = "Vãn Cung",
    
    
    
    ["#gongsunyuan"] = "Giáo Đồ Huyền Hải",
    ["gongsunyuan"] = "Công Tôn Uyên",
    ["huaiyi"] = "Hoài Dị",
    [":huaiyi"] = "Một lần trong giai đoạn hành động, bạn có thể mở toàn bộ bài trên tay ra, nếu bài nhiều hơn 1 màu, bạn chọn 1 màu và bỏ những lá trên tay có màu này, chọn tối đa X người có bài, thu lấy 1 lá của từng người (X là số lá bạn vừa bỏ), đặt tất cả trang bị bạn vừa thu lấy lên tướng này, gọi là [Dị]. Bạn có thể sử dụng hoặc đánh ra [Dị] như bài trên tay.",
    ["zisui"] = "Tứ Tuy",
    [":zisui"] = "Tỏa định kỹ, Giai đoạn rút bài, nếu có [Dị], rút thêm X lá (X là số [Dị]). Giai đoạn kết thúc, nếu số [Dị] lớn hơn giới hạn máu của bạn, bạn lập tức tử vong.",
    
    ["@huaiyi-choose"] = "Hoài Dị: Chọn 1 màu để bỏ bài",
    ["@huaiyi-snatch"] = "Hoài Dị: Chọn tối đa %arg người, lần lượt thu lấy 1 lá của họ.",
    ["huaiyi:red"] = "Đỏ",
    ["huaiyi:black"] = "Đen",
    
    ["&disloyalty"] = "Di",

	["#test"] = "%arg",
	
	["#pengyang"] = "Giang Dương Thái Thú",
	["pengyang"] = "Bành Dạng",
	["daming"] = "Đạt Mệnh",
	[":daming"] = "Đầu giai đoạn hành động của người cùng thế lực, bạn có thể bỏ 1 công cụ, bạn đưa 1 người đang không trong trạng thái liên hoàn vào trạng thái liên hoàn, bạn rút X lá (X là số người trong trạng thái liên hoàn), chọn:\n1. Sử dụng [Đào] với người đang có lượt; 2. Người đang có lượt sử dụng [Sát Lôi] với người do bạn chọn.",
	["xiaoni"] = "Hiêu Nghịch",
	[":xiaoni"] = "Tỏa định kỹ, sau khi bạn chỉ định mục tiêu hoặc trở thành mục tiêu của [Sát] hoặc công cụ phổ thông, nếu có người khác cùng thế lực với bạn và tất cả họ có số bài trên tay không nhiều hơn bạn, bạn lệnh tất cả mục tiêu không thể hưởng ứng với lá này.",
	
	["@daming"] = "Có thể phát động \"Đạt Mệnh\" với %dest, bỏ 1 công cụ.",
	["@daming-chain"] = "Đạt Mệnh: Chọn người để đưa vào trạng thái liên hoàn.",
	["@daming-choice"] = "Đạt Mệnh: Chọn hiệu quả muốn %dest chấp hành",
	["daming:peach"] = "Sử dụng [Đào]",
	["daming:slash"] = "Sử dụng [Sát Lôi]",
	["@daming-slash"] = "Đạt Mệnh: Chọn mục tiêu để %dest sử dụng [Sát Lôi]",
	
	

    ["tongling"] = "Thông Linh",
    [":tongling"] = "Một lần trong giai đoạn hành động, sau khi bạn gây sát thương cho 1 người không cùng thế lực (A), bạn có thể chọn 1 người cùng thế lực (B), B có thể sử dụng 1 lá với A; nếu lá này gấy sát thương, bạn và B rút 2 lá; nếu không gây sát thương, bạn lệnh A thu lấy lá bạn đã sử dụng để gây sát thương.",
    ["jinxian"] = "Cận Hãm",
    [":jinxian"] = "Sau khi bạn mở tướng này, bạn lệnh tất cả người trong khoảng cách 1:\n* Nếu họ đã mở tất cả tướng, họ úp 1 tướng\n* Nếu họ có tướng đang úp, họ bỏ 2 lá.",
    
    
    ["@tongling-invoke"] = "Có thể phát động \"Thông Linh\", chọn 1 người sử dụng bài lên %dest",
    ["@tongling-usecard"] = "Thông Linh: Chọn 1 lá bài để sử dụng lên %dest",
    ["@jinxian-hide"] = "Cận Hãm: chọn ẩn 1 tướng của bạn",
    ["jinxian_hide:head"] = "Chủ tướng",
    ["jinxian_hide:deputy"] = "Phó tướng",

	
	["#sufei"] = "Hùng Mãnh Dật Tài",
	["sufei"] = "Tô Phi",
	["lianpian"] = "Liên Phiên",
	[":lianpian"] = "Giai đoạn kết thúc của 1 người, nếu trong lượt này tổng số bài họ đã bỏ của tất cả người chơi lớn hơn số máu của bạn, nếu là lượt của bạn, bạn có thể lệnh 1 người cùng thế lực bổ sung bài trên tay đến giới hạn máu của họ; nếu là lượt của người khác, họ có thể chọn bỏ 1 lá của bạn hoặc lệnh bạn hồi 1 máu.",
	
	["@lianpian-target"] = "Có thể phát động \"Liên Phiên\", chọn 1 người bổ sung bài trên tay đến giới hạn máu?",
	["@lianpian"] = "Có thể phát động \"Liên Phiên\" của %src",
	["#lianpian-other"] = "Liên Phiên",
	["lianpian:discard"] = "Bỏ 1 lá của họ.",
	["lianpian:recover"] = "Lệnh họ hồi 1 máu.",
	
	["#liuba"] = "Sắc Hành Chỉnh Thân",
	["liuba"] = "Lưu Ba",
	["tongdu"] = "Trù Độ",
	[":tongdu"] = "Giai đoạn kết thúc của người cùng thế lực, họ có thể rút X lá (X là số bài họ đã bỏ trong giai đoạn bỏ bài ở lượt này, tối đa 3",
	["qingyin"] = "Quy Ẩn",
	[":qingyin"] = "Hạn định kỹ, giai đoạn hành động, bạn chọn tất cả người cùng thế lực (Áp dụng sau khi bạn đã mở tướng này), lần lượt hồi máu đến tối đa; sau đó bạn loại bỏ tướng này.",
	["@tongdu"] = "Có thể phát động \"Trù Độ\" của %src",
	["#tongdu-other"] = "Trù Độ",
	
	["#zhuling"] = "Kiên Thành Túc Tướng",
	["zhuling"] = "Chu Linh",
	["juejue"] = "Trấn Vệ",
	[":juejue"] = "Đầu giai đoạn bỏ bài, bạn có thể mất 1 máu, khi giai đoạn này kết thúc, nếu trong giai đoạn này bạn có bỏ bài, bạn lệnh tất cả người khác chọn:\n1. Đưa X lá trên tay vào chồng bài bỏ (X là số lá bạn đã bỏ trong giai đoạn này);\n2. Nhận 1 sát thương từ bạn.\nKhi bạn giết người cùng thế lực với bạn, bỏ qua chấp hành thưởng phạt.",
	["fangyuan"] = "Ngư Lân",
	[":fangyuan"] = "Trận pháp kỹ,\n1. Nếu bạn là người vây công trong quan hệ vây công, giới hạn trữ bài của người vây công +1, giới hạn trữ bài của người bị vây công -1.\n2. Giai đoạn kết thúc, nếu bạn là người bị vây công trong quan hệ vây công, bạn xem như sử dụng [Sát] với 1 người vây công",
	["@fangyuan-slash"] = "Ngư Lân: chọn 1 người đang vây công bạn, xem như sử dụng [Sát] với họ",
	
	["@juejue-discard"] = "Trấn Vệ: Bỏ %arg lá trên tay, hoặc %src gây 1 sát thương với bạn.",
	
	["#fangyuan-maxcards"] = "Ngư Lân",


}
