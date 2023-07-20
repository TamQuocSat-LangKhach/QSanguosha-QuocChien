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
	
	["overseas"] = "SP",
	["removed"] = "SP - Tiêu Trừ",

	["beimihu"] = "Himiko",
	["#beimihu"] = "Yamatai Đích Nữ Vương",
	["guishu"] = "Quỷ Thuật",
	[":guishu"] = "Bạn có thể chuyển hóa sử dụng 1 lá BÍCH trên tay thành [Tri Bỉ Tri Kỷ]/[Viễn Giao Cận Công];\n‣ Bạn cần sử dụng xen kẽ 2 lá trên theo cách này trong cùng 1 lượt." ,
	["yuanyu"] = "Viễn Vực",
	[":yuanyu"] = "Tỏa định kỹ: Khi bạn tính toán sát thương phải nhận, nếu bạn không thuộc tầm đánh của nguồn sát thương, sát thương này -1.",

	["caozhen"] = "Tào Chân",
	["#caozhen"] = "Vạn Tải Bất San",
	["sidi"] = "Ty Địch",
	[":sidi"] = "\n• Sau khi người cùng thế lực với bạn nhận sát thương, nếu họ có bài và số loại [Ngự] của bạn < 3, bạn có thể phát động kỹ năng, họ có thể đặt 1 lá của họ lên tướng của bạn, gọi là [Ngự] (Không thể chọn lá cùng loại với những [Ngự] đã có).\n• Sau khi bắt đầu lượt của người thế lực khác bạn, bạn có thể đưa tối đa 3 [Ngự] vào chồng bài bỏ, đưa ra số lựa chọn khác nhau tương ứng với mỗi [Ngự]:\n"..
	"1. Bạn chọn 1 loại bài có cùng loại với 1 trong số [Ngự] vừa bỏ, họ không thể sử dụng loại bài này trong lượt này;\n2. Bạn chọn 1 kỹ năng của tướng đã mở của họ, vô hiệu kỹ năng đó trong lượt này;\n3. Bạn lệnh họ chọn 1 người khác có cùng thế lực với bạn, người này hồi 1 màu.",

	["drive"] = "Ngự",

	["@sidi-put"] = "Ty Địch: Có thể chọn 1 lá đặt lên %src để làm [Ngự]",
	["@sidi-remove"] = "Có thể phát động »Ty Địch« với %dest",
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
	[":dangxian"] = "Tỏa định kỹ:\n• Sau khi bạn mở tướng này lần đầu tiên, bạn nhận 1 tiêu ký [Tiên Khu].\n• Sau khi bắt đầu lượt, bạn nhận 1 giai đoạn ra bài/.",

	["#zhugejin"] = "Liên Minh Đích Duy Hệ Giả",
	["zhugejin"] = "Gia Cát Cẩn",
	["huanshi"] = "Hoãn Thích",
	[":huanshi"] = "Khi phán xét của người cùng thế lực với bạn có hiệu lực, bạn có thể đánh ra 1 lá để thay thế kết quả phán xét đó.",
	["hongyuan"] = "Hoằng Viện",
	[":hongyuan"] = "\n•Khi bạn rút bài vì hiệu quả của »Hợp Tung«, bạn có thể lệnh 1 người khác có cùng thế lực với bạn rút bài thay bạn.\n• Một lần trong giai đoạn ra bài, bạn có thể mở 1 lá trên tay, lá đó khi ở trên tay bạn trong giai đoạn này xem như có ký hiệu »Hợp Tung«.",
	["mingzhe"] = "Minh Triết",
	[":mingzhe"] = "Ngoài lượt của bạn:\n• Khi bạn sử dụng/đánh ra lá Đỏ, bạn có thể rút 1 lá.\n• Khi bạn mất đi bài trong vùng trang bị, nếu trong đó có lá Đỏ, bạn có thể rút 1 lá",

	["@huanshi-card"] = CommonTranslationTable["@askforretrial"],
	["hongyuan-invoke"] = "Có thể phát động »Hoằng Viện«, chọn 1 người nhận bài",
	
	["#quancong"] = "Mộ Thế Diệu Tộc",
    ["quancong"] = "Toàn Tông",
    ["qinzhong"] = "Thân Trùng",
    [":qinzhong"] = "Phó tướng kỹ: Sau khi bắt đầu lượt, bạn có thể hoán đổi phó tướng của bạn với 1 người cùng thế lực với bạn.",
    ["zhaofu"] = "Chiêu Phụ",
    [":zhaofu"] = "\n• Khi bắt đầu giai đoạn ra bài, nếu tổng số [Thưởng] của tất cả người khác < 3, bạn có thể bỏ 1 lá và chọn 1 người khác, họ tăng 1 [Thưởng].\n• Sau khi lá cơ bản/công cụ phổ thông do người có [Thưởng] sử dụng kết toán xong, bạn có thể lệnh họ giảm 1 [Thưởng], xem như bạn sử dụng lá đó.",

    ["reward"] = "Thưởng",
    
    ["qinzhong-invoke"] = "Có thể phát động »Thân Trùng«, hoán đổi phó tướng với 1 người cùng thế lực.",
    ["@zhaofu1"] = "Có thể phát động »Chiêu Phụ«, bỏ 1 lá để 1 người được nhận [Thưởng]",
    ["zhaofu:prompt"] = "Có thể phát động »Chiêu Phụ«, xem như sử dụng [%arg]",
    ["@zhaofu2"] = "Có thể phát động »Chiêu Phụ«, xem như sử dụng [%arg]",
	
	["#guohuai"] = "Thùy Vấn Tần Ung",
    ["guohuai"] = "Quách Hoài",
    ["jingce"] = "Tinh Sách",
    [":jingce"] = "Giai đoạn ra bài, sau khi lá thứ X do bạn sử dụng kết toán xong (X là số máu hiện tại của bạn), nếu không có ai đang giải quyết hấp hối, bạn có thể yêu cầu 1 người thế lực khác bạn chấp hành 1 [Quân Lệnh]: Nếu họ không chấp hành, bạn rút 2 lá.",
    ["jingce-invoke"] = "Có thể phát động »Tinh Sách«, chọn 1 người khác thế lực chấp hành quân lệnh.",

    ["#yangxiu"] = "Thị Tài Phóng Khoáng",
    ["yangxiu"] = "Dương Tu",
    ["danlao"] = "Đạm Lạc",
    [":danlao"] = "Sau khi bạn trở thành mục tiêu của lá công cụ, nếu số mục tiêu của lá này > 1, bạn có thể rút 1 lá, sau đó lệnh lá này không có hiệu quả với bạn.",
    ["jilei"] = "Kê Lặc",
    [":jilei"] = "Sau khi bạn nhận sát thương, nếu sát thương này có nguồn, bạn có thể chọn 1 loại bài, lệnh nguồn sát thương trong lượt này không thể sử dụng, đánh ra hoặc bỏ lá trên tay thuộc loại bài này.",
    ["#Jilei"] = "«<font color=«yellow«><b>Kê Lặc</b></font>« có hiệu lực, %from không thể sử dụng, đánh ra hoặc bỏ %arg trên tay.",
    ["@jilei-choose"] = "Kê lặc: Chọn loại bài để %dest không thể sử dụng, đánh ra hoặc bỏ.",

    ["#zumao"] = "Bích Huyết Nhiễm Xích Trách",
    ["zumao"] = "Tổ Mậu",
    ["yinbingx"] = "Dẫn Binh",
    [":yinbingx"] = "\n• Khi bắt đầu giai đoạn kết thúc, bạn có thể đặt tùy ý lá phi cơ bản lên tướng này, gọi là [Trách].\n• Sau khi bạn nhận sát thương từ [Sát] hoặc [Quyết Đấu], bạn bỏ 1 [Trách].",
    ["@yinbing-put"] = "Có thể phát động »Dẫn Binh«, đặt 1 lá phi cơ bản vào [Trách]",
    ["kerchief"] = "Trách",
    ["juedi"] = "Tuyệt Địa",
    [":juedi"] = "Tỏa định kỹ:\n• Thần lực luôn ở bên bạn.\n• Khi bắt đầu giai đoạn chuẩn bị, nếu bạn có [Trách], bạn chọn 1 mục:\n1. Bỏ tất cả lá [Trách], bổ sung bài trên tay tới giới hạn máu;\n2. Giao tất cả [Trách] cho 1 người khác có số máu ≤ bạn, lệnh họ hồi 1 máu và rút bài bằng số [Trách] bạn đã giao.",
    ["juedi:self"] = "Bỏ [Trách] và bổ sung bài",
    ["juedi:give"] = "Giao [Trách] cho người khác",
    ["@juedi"] = "Tuyệt địa: Chọn 1 người khác có giới hạn máu không lớn hơn bạn.",

    ["#fuwan"] = "Trầm Nghị Đích Quốc Trượng",
    ["fuwan"] = "Phục Hoàn",
    ["moukui"] = "Mưu Hội",
    [":moukui"] = "Sau khi bạn xác định mục tiêu của [Sát], ứng với mỗi mục tiêu, bạn có thể chọn 1 mục:\n1. Rút 1 lá;\n2. Bỏ 1 lá của mục tiêu của [Sát] này;\n‣ Sau khi [Sát] này bị triệt tiêu bởi [Thiểm] của mục tiêu, họ bỏ 1 lá của bạn.",
    ["@moukui-choose"] = "Mưu Hội: Chọn rút 1 lá hoặc bỏ 1 lá của %dest",
    ["moukui:draw"] = "Rút 1 lá",
    ["moukui:discard"] = "Bỏ 1 lá",

    ["#MoukuiDiscard"] = "Đã phát động »%arg«, %to bỏ 1 lá của %from",

    ["#chendao"] = "Bạch Nhị Đốc",
    ["chendao"] = "Trần Đáo",
    ["wanglie"] = "Vãng Liệt",
    [":wanglie"] = "\n• Lá đầu tiên bạn sử dụng trong giai đoạn ra bài không giới hạn khoảng cách.\n• Giai đoạn ra bài, khi bạn sử dụng [Sát] hoặc công cụ phổ thông, bạn có thể lệnh cho tất cả mọi người không được hưởng ứng với lá này; nếu làm vậy, bạn không thể sử dụng bài trong giai đoạn này.",
	["dizai"] = "Địa Tải",
	[":dizai"] = "Trận pháp kỹ: Nếu bạn là người vây công trong quan hệ vây công, khi người vây công gây sát thương cho mục tiêu bị vây công của lá [Sát], người vây công còn lại có thể bỏ 1 lá để lệnh sát thương này +1.",
	["@dizai_discard"] = "Địa Tải: Có thể bỏ 1 lá để lệnh sát thương %src gây cho %dest +1",

    ["#tianyu"] = "Quy Lược Minh Luyện",
    ["tianyu"] = "Điền Dự",
    ["zhenxi"] = "Chấn Tập",
    [":zhenxi"] = "Sau khi bạn xác định mục tiêu của [Sát], ứng với mỗi mục tiêu, bạn có thể chọn 1 mục:\n1. Bạn bỏ 1 lá của họ;\n2. Bạn chuyển hóa 1 lá TÉP không phải công cụ như [Binh Lương Thốn Đoạn] hoặc 1 lá RÔ không phải công cụ như [Lạc Bất Tư Thục] không giới hạn khoảng cách với họ;\n‣ Nếu bạn đã mở 2 tướng và họ có tướng đang úp, bạn có thể chấp hành cả 2 mục với thứ tự tùy ý.",
    ["jiansu"] = "Kiệm Tố",
    [":jiansu"] = "Phó tướng kỹ, Giảm 0.5 máu gốc:\n• Khi bạn nhận bài ngoài lượt, bạn có thể gọi những lá này trên tay bạn là [Kim] chừng nào lá đó còn trên tay bạn, [Kim] luôn công khai với những người khác.\n• Khi bắt đầu giai đoạn ra bài, bạn có thể bỏ đi tùy ý [Kim], sau đó chọn 1 người đã bị thương có số máu ≤ số [Kim] đã bỏ, lệnh họ hồi 1 máu.",
    ["@zhenxi-choose"] = "Chấn Tập: Chọn sử dụng 1 lá Công cụ thời gian đã chuyển hóa lên %dest hoặc bỏ 1 lá của họ.",
    ["zhenxi:usecard"] = "Chuyển hóa 1 công cụ thời gian",
    ["zhenxi:discard"] = "Bỏ 1 lá",
    ["@zhenxi-trick"] = "Chấn Tập: Sử dụng lá phi công cụ RÔ như [Lạc Bất Tư Thục] hoặc phi công cụ TÉP như [Binh Lương Thốn Đoạn] lên %dest",
    ["@zhenxi-discard"] = "Chấn Tập: Bỏ 1 lá của %dest",
    ["@jiansu-card"] = "Có thể phát động »Kiệm Tố«, bỏ [Kim] và lệnh 1 người hồi máu.",
	["money"] = "Kim",


    ["#maliang"] = "Bạch Mi Lệnh Sĩ",
    ["maliang"] = "Mã Lương",
    ["mumeng"] = "Mục Minh",
    [":mumeng"] = "Một lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá CƠ trên tay thành [Viễn Giao Cận Công]/[Lục Lực Đồng Tâm]",
    ["naman"] = "Nạp Man",
    [":naman"] = "Khi người khác sử dụng bài Đen có chỉ định nhiều mục tiêu, bạn có thể tiến hành phán xét, nếu kết quả phát xét không phải BÍCH, bạn chọn 1 mục:\n1. Lệnh 1 người khác trở thành mục tiêu của bài (Không bị giới hạn khoảng cách);\n2. Hủy bỏ mục tiêu đối với 1 mục tiêu của lá đó.",

    ["@naman-target"] = "Nạp Man: Thêm hoặc bớt 1 mục tiêu của [%arg] do %src sử dụng",
	
	["#huaxiong"] = "Ma Tướng",
    ["huaxiong"] = "Hoa Hùng",
    ["yaowu"] = "Diệu Võ",
    [":yaowu"] = "Hạn định kỹ: Sau khi bạn gây sát thương, nếu tướng này đang úp mặt, bạn có thể phát động kỹ năng này: Bạn tăng 2 giới hạn máu, hồi 2 máu;\n‣ Sau khi bạn trận vong, tất cả người cùng thế lực với bạn mất 1 máu.",
    ["shiyong"] = "Thị Dũng",
    [":shiyong"] = "Tỏa định kỹ: Khi bạn tính toán sát thương phải nhận, nếu sát thương này đến từ lá bài:\n- Nếu bạn chưa phát động »Diệu Võ« và lá gây ra sát thương không phải màu Đỏ, bạn rút 1 lá;\n- Nếu bạn đã phát động »Diệu Võ« và lá gây sát thương không phải màu Đen, nguồn sát thương rút 1 lá.",

    ["#zhangchunhua"] = "Lãnh Huyết Hoàng Hậu",
    ["zhangchunhua"] = "Trương Xuân Hoa",
    ["guojue"] = "Quả Quyết",
    [":guojue"] = "\n• Sau khi bạn mở tướng này lần đầu tiên, bạn gây 1 sát thương cho 1 người khác.\n• Khi 1 người khác tiến vào trạng thái hấp hối do bạn gây sát thương, bạn có thể bỏ 1 lá của họ.",
    ["shangshi"] = "Thương Thệ",
    [":shangshi"] = "Sau khi bạn nhận sát thương, bạn có thể chọn bỏ 1 lá hoặc giao X lá trên tay bạn cho 1 người khác; nếu làm vậy, bạn rút X lá (X lá số máu bạn đã mất).",
    ["@guojue-damage"] = "Quả quyết: Chọn 1 người khác để gây 1 sát thương",
    ["@shangshi-card"] = "Có thể phát động »Thương Thệ«, chọn bỏ 1 lá hoặc giao %arg lá trên tay cho 1 người khác",
    ["@shangshi-card-full"] = "Có thể phát động »Thương Thệ«, chọn bỏ 1 lá",

	["#liufuren"] = "Khốc Đố Đích Hải Đường",
	["liufuren"] = "Lưu Phu Nhân",
	["zhuidu"] = "Truy Đố",
	[":zhuidu"] = "Một lần trong giai đoạn ra bài, khi bạn gây sát thương, bạn có thể lệnh người nhận sát thương chọn 1 mục:\n1. Sát thương này +1;\n2. Nếu họ có lá trong vùng trang bị, bỏ đi tất cả bài trong vùng trang bị;\n‣ Nếu họ có giới tính nữ, bạn có thể bỏ 1 lá, lệnh họ thực hiện cả 2 mục.",
	["shigong"] = "Kỳ Cung",
	[":shigong"] = "Hạn định kỹ: Ngoài lượt của bạn, khi bạn tiến vào trạng thái hấp hối, bạn có thể loại bỏ Phó tướng của bạn, sau đó lệnh người đang có lượt chọn 1 mục:\n1. Họ nhận 1 kỹ năng không phân loại từ lá tướng mà bạn vừa loại bỏ, lệnh bạn hồi đầy máu;\n2. Lệnh bạn hồi đến 1 máu.",

	["@zhuidu-both"] = "Truy Đố: Có thể bỏ 1 lá và lệnh %dest thực hiện 2 mục",
	["zhuidu_choice"] = "Truy Đố",
	["zhuidu_choice:throw"] = "Bỏ tất cả bài trong vùng trang bị",
	["zhuidu_choice:damage"] = "Sát thương +1",
	
	["@shigong-choose"] = "Kỳ Cung: Có thể nhận 1 kỹ năng của %arg",
	    
    ["#yijibo"] = "Kiến lễ vu thế",
    ["yijibo"] = "Y Tịch",
    ["dingke"] = "Định Khoa",
    [":dingke"] = "Một lần trong lượt của mỗi người, sau khi 1 người cùng thế lực với bạn mất bài ngoài lượt không vì sử dụng/đánh ra, bạn có thể chọn 1 mục:\n1. Giao 1 lá trên tay cho họ;\n2. Lệnh người đang có lượt bỏ 1 lá trên tay;\n‣ Nếu số [Âm dương ngư] của bạn nhỏ hơn giới hạn máu, bạn thu lấy 1 tiêu ký [Âm dương ngư].",
    ["jiyuan"] = "Cấp Viện",
    [":jiyuan"] = "Khi có người tiến vào trạng thái hấp hối hoặc sau khi có người được bạn giao bài do phát động »Định Khoa«, bạn có thể lệnh họ rút 1 lá.",

	["dingke-invoke"] = "Có thể phát động »Định Khoa«, chọn %dest để lệnh họ bỏ 1 lá trên tay hoặc chọn người vừa mất bài để giao họ 1 lá trên tay",
    ["@dingke-give"] = "Định Khoa: Chọn 1 lá trên tay và giao cho %dest",
    
    ["#zhangyi"] = "Tranh Hổ",
    ["zhangyi"] = "Trương Dực",
    ["kangrui"] = "Kháng Nhuệ",
    [":kangrui"] = "Một lần trong giai đoạn ra bài của 1 người cùng thế lực với bạn, khi họ sử dụng bài có chỉ định 1 người khác làm mục tiêu duy nhất, bạn có thể hủy bỏ mục tiêu của lá đó, lệnh họ chọn 1 mục:\n1. Bổ sung bài trên tay đến X lá (X là số máu của họ), những người khác trong giai đoạn này không thể trở thành mục tiêu của bài do họ sử dụng;\n2. Nếu không có người trong trạng thái hấp hối, lệnh mục tiêu ban đầu của lá đó xem như sử dụng [Quyết đấu] với họ, số sát thương của [Quyết đấu] này +1.",
    
    ["kangrui:prompt"] = "Có thể phát động »Kháng Nhuệ«, hủy bỏ mục tiêu %dest từ lá [%arg] của %src",
    ["@kangrui-choose"] = "Kháng Nhuệ: Chọn bổ sung bài trên tay đến giới hạn máu hoặc lệnh %dest xem như sử dụng [Quyết Đấu] với bạn",
    ["kangrui:fillhandcards"] = "Bổ sung bài",
    ["kangrui:useduel"] = "Quyết Đấu",
    
    ["#chengpu"] = "Hổ Thủ",
    ["chengpu"] = "Trình Phổ",
    ["huxun"] = "Hổ Huân",
    [":huxun"] = "Khi 1 người kết thúc lượt, nếu trong lượt này có người tiến vào trạng thái hấp hối do bạn gây sát thương, bạn có thể chọn 1 mục:\n1. Nếu bạn không phải người duy nhất có giới hạn máu cao nhất, bạn tăng 1 giới hạn máu và hồi 1 máu;\n2. Bạn có thể di chuyển 1 lá trên bàn chơi.",
    ["yuancong"] = "Nguyên Tòng",
    [":yuancong"] = "Khi kết thúc giai đoạn ra bài của 1 người cùng thế lực với bạn, nếu trong giai đoạn này họ không gây sát thương, họ có thể giao 1 lá cho bạn, sau đó bạn có thể sử dụng 1 lá trên tay.",
    
    ["huxun:gainmaxhp"] = "Tăng giới hạn máu",
    ["huxun:movecard"] = "Di chuyển 1 lá trên bàn chơi.",
    ["@huxun-move"] = "Hổ Huân: Có thể di chuyển 1 lá trên bàn chơi.",
    ["@yuancong"] = "Có thể phát động »Nguyên Tòng« của %src",
    ["@yuancong-usecard"] = "Nguyên Tòng: Có thể sử dụng 1 lá trên tay.",
    
    
    ["#chengyu"] = "Thái Sơn Phụng Nhật",
    ["chengyu"] = "Trình Dục",
    ["shefu"] = "Phục Binh",
    [":shefu"] = "\n• Một lần trong giai đoạn ra bài, bạn có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Phục Binh].\n• Khi 1 người khác sử dụng bài trên tay, bạn có thể đưa 1 [Phục Binh] có cùng tên với lá đó vào chồng bài bỏ, hủy bỏ hoàn toàn lá đó.\n• Khi bắt đầu giai đoạn chuẩn bị, nếu số [Phục Binh] > 2, bạn đưa số [Phục Binh] vào chồng bài bỏ đến khi còn 2.",
    ["benyu"] = "Bí Dục",
    [":benyu"] = "Sau khi bạn nhận sát thương:\n• Nếu bài trên tay bạn ít hơn nguồn sát thương, bạn chọn 1 mục:\n1. Bổ sung bài trên tay đến khi bằng với họ, tối đa 5 lá;\n2. Lệnh họ bỏ đi bài trên tay đến khi bằng bạn, tối đa bỏ 5 lá.\n• Nếu bài trên tay bạn nhiều hơn nguồn sát thương, bạn có thể bỏ số bài trên tay bằng số bài trên tay họ +1, sau đó gây 1 sát thương cho họ.",

    ["#shefu-compulsory"] = "Phục Binh",
    ["ambush"] = "Phục Binh",
    ["@shefu-invoke"] = "Có thể phát động »Phục Binh«, bỏ 1 [Phục Binh] có tên [%arg] để hủy bỏ hoàn toàn lá [%arg] do %src sử dụng",
    ["@shefu-remove"] = "Phục Binh: chọn 1 [Phục Binh] để bỏ",
	
	["@benyu-invoke"] = "Có thể phát động »Bí Dục«, bỏ %arg lá trên tay để gây 1 sát thương cho %dest",
    ["@benyu-choose"] = "Bí Dục: Chọn phương pháp để bài trên tay bạn bằng với %dest",
    ["benyu:draw"] = "Bạn bổ sung bài",
    ["benyu:discard"] = "Họ bỏ bài",
	
	["#xiahoushang"] = "Ngụy Dận Tiền Khu",
	["xiahoushang"] = "Hạ Hầu Thượng",
	
	["tanfeng"] = "Tham Phong",
	[":tanfeng"] = "Khi bắt đầu giai đoạn chuẩn bị, bạn có thể bỏ 1 lá trong vùng chơi của 1 người thế lực khác bạn; nếu làm vậy, họ có thể chọn nhận 1 sát thương Hỏa từ bạn để lệnh bạn bỏ qua 1 giai đoạn trong lượt này, ngoại trừ giai đoạn chuẩn bị.",
	["@tanfeng-target"] = "Có thể phát động »Tham Phong«, chọn 1 người khác thế lực",
	["@tanfeng-choose"] = "Tham Phong: Có thể nhận 1 sát thương hỏa để lệnh %src bỏ qua 1 giai đoạn",


	["#guyong"] = "Miếu Đường Đích Ngọc Khách",
	["guyong"] = "Cố Ung",
	
	["lifu"] = "Lễ Phụ",
	[":lifu"] = "Một lần trong giai đoạn ra bài, bạn có thể chọn 1 người, lệnh họ bỏ 2 lá, sau đó bạn xem lá trên đầu chồng bài rút và giao cho họ.",
	["yanzhong"] = "Ngôn Trung",
	[":yanzhong"] = "Khi bắt đầu giai đoạn kết thúc, bạn có thể chọn 1 chất và chọn 1 người khác có bài trên tay, bạn bỏ 1 lá trên tay họ; nếu chất của lá đã bỏ và chất đã đoán:\n- Khác chất: bạn bỏ 1 lá;\n- Cùng chất và chất đó là:\nCƠ: Bạn hồi 1 máu;\nRÔ: Bạn rút 1 lá, loại bỏ trạng thái xích;\nTÉP: Họ giao 1 lá cho bạn;\nBÍCH: Họ mất 1 máu.",
	["lifu_view:prompt"] = "Lễ Phụ: Lá [%arg] này sẽ được giao cho %dest",
	["@yanzhong"] = "Có thể phát động »Ngôn Trung«, chọn 1 người khác có bài trên tay",
	["@yanzhong-give"] = "Ngôn Trung: Chọn 1 lá và giao cho %src",

	["#liyan"] = "Long Lý Toàn Vân",
	["liyan"] = "Lý Nghiêm",
	
	["jinwu"] = "Căng Võ",
	[":jinwu"] = "Khi bắt đầu giai đoạn ra bài, bạn có thể yêu cầu bạn chấp hành 1 quân lệnh:\n- Nếu chấp hành, bạn xem như sử dụng 1 [Sát];\n- Nếu không chấp hành, bạn kết thúc giai đoạn ra bài.",
	["zhuke"] = "Trúc Khoa",
	[":zhuke"] = "Chủ tướng kỹ, giảm 0.5 máu gốc:\n• Sau khi bạn chọn chấp hành quân lệnh, bạn có thể chọn lại quân lệnh để chấp hành.\n• Khi bạn nhận trạng thái xích hoặc trạng thái chồng tướng, bạn có thể lệnh 1 người cùng thế lực với bạn hồi 1 máu.",
	["quanjia"] = "Khuyến Giá",
	[":quanjia"] = "Phó tướng kỹ: Sau khi bạn mở tướng này lần đầu tiên, bạn phát động kỹ năng này, thực hiện lần lượt:\n- Triệu hoán thế lực, có thể hưởng ứng triệu hoán này mà không trở thành dã tâm;\n- Người cùng thế lực với bạn rút 1 lá\n- Người có kỹ năng »Nhân Đức« nhận kỹ năng »Chương Vũ« và »Thụ Việt«",

	["@jinwu-slash"] = "Căng Võ: Chọn 1 mục tiêu cho [Sát]",
	["zhuke-invoke"] = "Có thể phát động »Trúc Khoa« lệnh 1 người hồi 1 máu.",
	["@zhuke-select"] = "Trúc Khoa: Chọn 1 quân lệnh bạn muốn chấp hành.",
	
    ["#maxiumatie"] = "Tru Gian Nghĩa Tồn",
    ["maxiumatie"] = "Mã Hưu & Mã Thiết",
    ["&maxiumatie"] = "Mã Hưu Mã Thiết",
    ["illustrator:maxiumatie"] = "alien",
    --["designer:maxiumatie"] = "",
    ["mashu_maxiumatie"] = "Mã Thuật",
    ["kenshang"] = "Khẩn Thương",
    [":kenshang"] = "Bạn có thể chuyển hóa sử dụng tùy ý số lá của bạn thành [Sát] (ít nhất 1 lá);\n‣ Sau khi bạn chỉ định mục tiêu cho [Sát] này, bạn có thể lệnh tất cả người khác ở ngoài tầm đánh của bạn trở thành mục tiêu của [Sát] này (không giới hạn khoảng cách), hủy bỏ tất cả mục tiêu trong tầm đánh của bạn;\n‣ Sau khi lá [Sát] này kết toán, nếu số lá bạn đã đem sử dụng > X, bạn rút X lá; Ngược lại, bạn mất »Mã Thuật« hoặc »Khẩn Thương« (X là tổng số sát thương mà [Sát] này đã gây ra).",
    ["_kenshang:prompt"] = "Khẩn Thương: Có thể thay đổi mục tiêu thành tất cả người ngoài tầm đánh",
    ["@kenshang-choose"] = "Khấn Thương: Chọn 1 kỹ năng để mất đi",
    ["#KenshangTarget"] = "%from thay đổi mục tiêu của [Sát] thành %to ",
	
	["lord_ex"] = "Bất Thần",
	["lord_ex_card"] = "Bất Thần",
	
	
	["#mengda"] = "Đãi Quân Phản Phúc",
	["mengda"] = "Mạnh Đạt",
	["qiuan"] = "Cầu An",
	[":qiuan"] = "Khi bạn nhận sát thương, nếu bạn không có [Hàm], bạn có thể đem lá gây sát thương cho bạn đặt lên tướng này, gọi là [Hàm], sau đó chặn sát thương này.",
	["liangfan"] = "Lượng Phản",
	[":liangfan"] = "Tỏa định kỹ: Khi bắt đầu giai đoạn chuẩn bị, nếu bạn có [Hàm], bạn mất 1 máu, sau đó thu lấy tất cả [Hàm];\n‣ Trong lượt này, sau khi bạn gây sát thương cho 1 người do sử dụng [Hàm], bạn có thể thu lấy 1 lá của họ.",
	["letter"] = "Hàm",

	["#LiangfanEffect"] = "%from đã sử dụng [%arg] để gây sát thương và thu lấy 1 lá của %to",
	
	["@liangfan"] = "Lượng Phản: Lấy 1 lá của %dest",
	
	
	["#tangzi"] = "Đắc Thì Thức Phong",
	["tangzi"] = "Đường Tư",
	["xingzhao"] = "Hưng Thạo",
	[":xingzhao"] = "Tỏa định kỹ: Dựa theo số thế lực trên bàn chơi có người bị thương:\n- 1+: Bạn nhận kỹ năng »Tuân Tuân«;\n- 2+: Sau khi bạn nhận sát thương, giữa bạn và nguồn gây sát thương, người ít bài trên tay hơn rút 1 lá;\n- 3+: Khi bắt đầu giai đoạn bỏ bài, giới hạn trữ bài của bạn +4.\n- 4+: Khi bạn mất bài trong vùng trang bị, bạn rút 1 lá.",
	["xunxun_tangzi"] = "Tuân Tuân",
	
	["#zhanglu"] = "Chính Khoan Giáo Huệ",
	["zhanglu"] = "Trương Lỗ",
	["bushi"] = "Bố Thí",
	[":bushi"] = "\n• Khi kết thúc lượt, bạn nhận X [Nghĩa Xá] (X là số máu của bạn).\n• Khi bắt đầu giai đoạn chuẩn bị của người khác, nếu bạn có [Nghĩa Xá], bạn có thể giao 1 lá cho họ, sau đó bạn bỏ 1 [Nghĩa Xá] và rút 2 lá.\n• Khi bắt đầu giai đoạn chuẩn bị, bạn bỏ X lá (X là số người còn sống trừ số máu của bạn và trừ 2), sau đó bỏ tất cả [Nghĩa Xá].",
	["midao"] = "Mễ Đạo",
	[":midao"] = "\n• Khi bắt đầu giai đoạn kết thúc, nếu không có [Mễ], bạn có thể rút 2 lá, sau đó bạn đặt 2 lá lên tướng này, gọi là [Mễ].\n• Khi phán xét của 1 người có hiệu lực, bạn có thể đánh ra 1 [Mễ] để thay đổi kết quả phán xét, sau đó thu lấy lá phán xét ban đầu.",
    ["bushi:discard"] = "Có thể phát động »Bố Thí« để bỏ %arg lá",
    ["bushi:mark"] = "Có thể phát động »Bố Thí« để nhận [Nghĩa Xá]",
    ["yishe"] = "Nghĩa Xá",
    ["@bushi-give"] = "Có thể phát động »Nghĩa Xá« để giao 1 lá cho %src",
    ["rice"] = "Mễ",
    ["@midao-push"] = "Mễ Đạo: Chọn 2 lá để đặt [Mễ]",
    ["@midao-card"] = CommonTranslationTable["@askforretrial"],
	
	["#mifangfushiren"] = "Trục Giá Nghênh Trần",
	["mifangfushiren"] = "Mi Phương & Phó Sĩ Nhân",
	["&mifangfushiren"] = "Mi Phương Phó Sĩ Nhân",
	["fengshix"] = "Phong Thế",

	[":fengshix"] = "\n• Sau khi bài bạn sử dụng xác định 1 mục tiêu duy nhất, nếu số bài trên tay họ < bạn, bạn có thể bỏ 1 lá của bạn và họ, lệnh sát thương từ lá này +1.\n• Sau khi bạn trở thành mục tiêu duy nhất của bài do người khác sử dụng, nếu số lá trên tay bạn nhỏ hơn họ, họ có thể lệnh bạn bỏ 1 lá của bạn và họ, lệnh sát thương từ lá này +1.",
	
	["@fengshix"] = "Có thể phát động »Phong Thế« của %src",
	
	
	["#liuqi"] = "Cư Ngoại Nhi An",
	["liuqi"] = "Lưu Kỳ",
	["wenji"] = "Vấn Kế",
	[":wenji"] = "Khi bắt đầu giai đoạn ra bài, bạn có thể lệnh 1 người khác giao cho bạn 1 lá ngửa mặt:\n- Nếu họ cùng thế lực với bạn hoặc không có thế lực, lượt này bạn sử dụng lá này không giới hạn khoảng cách và số lần và không thể hưởng ứng;\n- Nếu họ thế lực xác định khác bạn, bạn giao cho họ 1 lá bài khác.",
	
	["tunjiang"] = "Truân Giang",
	[":tunjiang"] = "Khi bắt đầu giai đoạn kết thúc, nếu bạn trong giai đoạn ra bài đã sử dụng ít nhất 1 lá và không chỉ định người khác làm mục tiêu, bạn có thể rút X lá (X là số thế lực trên bàn chơi).",
	["@wenji"] = "Có thể kích »Vấn Kế«, chọn 1 người khác",
	["@wenji-give"] = "Vấn Kế, chọn 1 lá và giao cho %src",
	["#WenjiEffect"] = "%from đã phát động %arg, [%arg2] không thể bị phản ứng.",
	["#wenji-effect"] = "Vấn Kế",
	
	["#shixie"] = "Bách Việt Linh Y",
	["shixie"] = "Sĩ Nhiếp",
	["biluan"] = "Tị Loạn",
	[":biluan"] = "Tỏa định kỹ: Khoảng cách từ người khác tới bạn +X (X là số lá trong vùng trang bị của bạn).",
	["lixia"] = "Lễ Hạ",
	[":lixia"] = "Tỏa định kỹ: Khi bắt đầu giai đoạn chuẩn bị của người thế lực khác bạn, nếu bạn không ở trong tầm đánh của họ, bạn lệnh họ chọn 1 mục:\n1. Lệnh bạn rút 1 lá;\n2. Bỏ 1 lá trong vùng trang bị của bạn, sau đó họ mất 1 máu.",

    ["@lixia-choose"] = "Lễ Hạ: Chọn lệnh %src rút 1 lá hoặc bỏ 1 lá trong vùng trang bị của %src và mất 1 máu",
    ["lixia:draw"] = "Rút bài",
    ["lixia:discard"] = "Bỏ trang bị",

    ["#zhonghui"] = "Kiệt Ngạo Đích Dã Tâm Gia",
    ["zhonghui"] = "Chung Hội",
    ["quanji"] = "Quyền Kế",
    [":quanji"] = "\n• Một lần trong lượt ứng với mỗi thời điểm, sau khi bạn gây hoặc nhận sát thương, bạn có thể rút 1 lá, sau đó đặt ngửa 1 lá lên tướng này, gọi là [Quyền].\n• Giới hạn trữ bài của bạn +X (X là số [Quyền]).",
    ["paiyi"] = "Bài Dị",
    [":paiyi"] = "Một lần trong giai đoạn ra bài, bạn có thể đưa 1 [Quyền] vào chồng bài bỏ và chọn 1 người, họ rút X lá (X là số [Quyền] bạn có, tối đa 7);\n‣ Nếu số bài trên tay họ > bạn, bạn gây 1 sát thương cho họ.",

    ["@quanji-push"] = "Quyền Kế: Đặt 1 lá lên tướng làm [Quyền]",
    ["power_pile"] = "Quyền",


    ["#dongzhao"] = "Di Tôn Dị Đỉnh",
    ["dongzhao"] = "Đổng Chiêu",
    ["quanjin"] = "Khuyến Tiến",
    [":quanjin"] = "Một lần trong giai đoạn ra bài, bạn có thể giao 1 lá trên tay cho người từng nhận sát thương trong giai đoạn này và lệnh họ chấp hành 1 [Quân Lệnh]:\n- Nếu họ chấp hành, bạn rút 1 lá;\n- Nếu họ không chấp hành và bạn không phải người có nhiều bài trên tay nhất, bạn bổ sung bài trên tay đến khi bằng người có nhiều bài trên tay nhất, tối đa 5 lá.",
    ["zaoyun"] = "Tạc Vận",
    [":zaoyun"] = "Một lần trong giai đoạn ra bài, bạn có thể chọn 1 người thế lực xác định với bạn và khoảng cách từ bạn đến họ lớn hơn 1 và bỏ X lá bài trên tay (X là khoảng cách từ bạn đến họ -1), lệnh khoảng cách từ bạn đến họ là 1 trong lượt này, sau đó bạn gây 1 sát thương cho họ.",

    ["#xushu"] = "Nan Vi Hoàn Thần",
    ["xushu"] = "Từ Thứ",
    ["qiance"] = "Khiêm Sách",
	[":qiance"] = "Sau khi người cùng thế lực với bạn xác định mục tiêu của lá công cụ, họ có thể lệnh những mục tiêu thuộc Đại thế lực không thể hướng ứng với lá này.",
	["jujian"] = "Cử Tiến",
	[":jujian"] = "Phó tướng kỹ, giảm 0.5 máu gốc: Khi 1 người cùng thế lực với bạn tiến vào trạng thái hấp hối, bạn có thể lệnh họ hồi đến 1 máu, sau đó bạn đổi Phó tướng.",
	["@qiance"] = "Có thể phát động »Khiêm Sách« của %src",
    
    ["#wujing"] = "Hàn Mã Lưu Kim",
    ["wujing"] = "Ngô Cảnh",
    ["diaogui"] = "Điều Quy",
    [":diaogui"] = "Một lần trong giai đoạn ra bài, có thể sử dụng 1 lá trang bị như [Điệu Hổ Ly Sơn];\n‣ Nếu bằng cách này thế lực của bạn có sự thay đổi về đội hình, bạn rút X lá (X là số người của đội hình đông nhất trong những quan hệ đội hình ở thế lực của bạn có sự thay đổi).",
    ["fengyang"] = "Phong Dương",
    [":fengyang"] = "Trận pháp kỹ: Người thế lực xác định khác bạn không thể thu lấy hoặc bỏ trang bị của người cùng đội hình với bạn.",

    ["#yanbaihu"] = "Sài Nha Lạc Giản",
    ["yanbaihu"] = "Nghiêm Bạch Hổ",
    ["zhidao"] = "Trĩ Đạo",
    [":zhidao"] = "Tỏa định kỹ: Khi bắt đầu giai đoạn ra bài, bạn chọn 1 người khác, trong lượt này:\n- Khoảng cách từ bạn đến họ là 1;\n- Người khác ngoại trừ họ không thể trở thành mục tiêu của bài do bạn sử dụng;\n- Sau khi bạn gây sát thương cho họ lần đầu tiên trong giai đoạn này, bạn thu lấy 1 lá trong vùng chơi của họ.",
    ["jilix"] = "Ký Li",
    [":jilix"] = "Tỏa định kỹ:\n• Sau khi kết toán xong lá cơ bản Đỏ hoặc công cụ phổ thông Đỏ, nếu bạn là mục tiêu duy nhất của lá này, bạn lệnh cho người sử dụng xem như sử dụng lá cùng tên với lá đó với bạn (không giới hạn khoảng cách, số lần sử dụng);\n• Khi bạn nhận sát thương lần thứ 2 trong cùng 1 giai đoạn, bạn chặn sát thương và loại bỏ tướng này.",
    
    ["#zhidao-damage"] = "Trĩ Đạo",
    ["@zhidao-target"] = "Trĩ Đạo: Chọn 1 người khác",
    ["#ZhidaoEffect"] = "%from đã phát động »%arg«, nhận 1 lá trong vùng chơi của %to",
    
    ["jilix:target"] = "Có thể phát động »Ký Li«, lệnh %src 1 lần nữa xem như sử dụng [%arg] với bạn.",
    ["jilix:damage"] = "Có thể phát động »Ký Li«, chặn sát thương và loại bỏ tướng này.",

    ["ImperialEdict"] = "Chiếu Thư",
    [":ImperialEdict"] = "Bài Trang bị - Bảo vật\n\n<b>Kỹ năng</b>:\n" ..
                    "\n• Sau khi sử dụng lá này, bạn đặt lá này vào vùng tướng của bạn.\n" ..
					"\n• Một lần trong giai đoạn ra bài của người có cùng thế lực với bạn, nếu họ thuộc tiểu thế lực, có thể đặt tối đa 2 lá trên tay lên tướng của bạn; nếu không thuộc tiểu thế lực, họ có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Chiếu].\n" ..
                    "\n• Một lần trong giai đoạn ra bài, nếu có 4 [Chiếu] không cùng chất, bạn có thể đưa tất cả [Chiếu] vào chồng bài bỏ, rút ngẫu nhiêu 1 lá công cụ thế lực.\n" ,

    ["imperialedictattach"] = "Đặt bài trên tay",
    [":imperialedictattach"] = "Một lần trong giai đoạn ra bài của người có cùng thế lực với bạn, nếu họ thuộc tiểu thế lực, có thể đặt tối đa 2 lá trên tay lên tướng của bạn; nếu không thuộc tiểu thế lực, họ có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Chiếu].",
    ["imperialedicttrick"] = "Nhận bài công cụ",
    [":imperialedicttrick"] = "Một lần trong giai đoạn ra bài, nếu có 4 lá [Chiếu] không cùng chất, bạn có thể đưa tất cả [Chiếu] vào chồng bài bỏ, rút ngẫu nhiêu 1 lá công cụ thế lực.",

    ["rule_the_world"] = "Hiệu Lệnh Thiên Hạ",
    [":rule_the_world"] = "Bài công cụ - Ngụy\n\nMục tiêu: Một người không phải ít máu nhất\nHiệu quả: Ngoại trừ mục tiêu, mỗi người có thể lựa chọn 1 mục:\n1. Bỏ 1 lá trên tay và xem như sử dụng [Sát] không giới hạn khoảng cách với mục tiêu (Người thế lực Ngụy không cần bỏ bài);\n2. Bỏ 1 lá của mục tiêu (Người thế lực Ngụy thu lấy lá đó thay vì bỏ).",
    ["rule_the_world:slash"] = "%log xem như sử dụng [Sát] với %to",
    ["rule_the_world:discard"] = "Một lá bài của %to bị %log",
    ["rule_the_world_slash"] = "Bỏ 1 lá bài và",
    ["rule_the_world_discard"] = "bỏ đi",
    ["rule_the_world_getcard"] = "thu lấy",
    ["@rule_the_world-slash"] = "Hiệu Lệnh Thiên Hạ: Bỏ 1 lá trên tay, xem như sử dụng [Sát] với %dest.",

    ["conquering"] = "Khắc Phục Trung Nguyên",
    [":conquering"] = "Bài công cụ - Thục\n\nMục tiêu: Tùy ý\nHiệu quả: Mục tiêu lựa chọn 1 mục:\n1. Xem như sử dụng [Sát] (Khi người thế lực Thục gây sát thương do sử dụng [Sát] này, sát thương +1);\nRút 1 lá (Người thế lực Thục đổi thành rút 2 lá).",
    ["@conquering-slash"] = "Khắc Phục Trung Nguyên: Chọn mục tiêu, xem như sử dụng [Sát], hoặc bấm »Hủy bỏ« để rút bài. ",

    ["consolidate_country"] = "Cố Quốc An Bang",
    [":consolidate_country"] = "Bài công cụ - Ngô\n\nMục tiêu: Bạn\nHiệu quả: Mục tiêu rút 8 lá sau đó bỏ ít nhất 6 lá trên tay, nếu bạn thuộc thế lực Ngô, có thể giao tùy ý tối đa 6 lá trong số những lá bỏ cho người khác thuộc thế lực Ngô, mỗi người tối đa 2 lá.",

    ["@consolidate_country-discard"] = "Cố Quốc An Bang: Chọn tối thiểu 6 lá trên tay để bỏ",
    ["@consolidate_country-give"] = "Cố Quốc An Bang: Có thể giao 6 lá cho người thế lực Ngô khác, tối đa 2 lá mỗi người.",

    ["chaos"] = "Văn Hòa Loạn Võ",
    [":chaos"] = "Bài công cụ - Quần\n\nMục tiêu: Tất cả\nHiệu quả: Mục tiêu mở bài trên tay, sau đó bạn chọn 1 mục:\n1. Lệnh họ bỏ 2 lá khác loại trên tay;\n2. Bỏ 1 lá trên tay họ;\nNgười thế lực Quần sau khi chấp hành lựa chọn của bạn, nếu họ không có bài trên tay, họ bổ sung bài trên tay tới máu hiện tại.",
    
    ["chaos:letdiscard"] = "Lệnh %to bỏ 2 lá không cùng loại trên tay",
    ["chaos:discard"] = "Bỏ 1 lá trên tay %to",

    ["@chaos-select"] = "Văn Hòa Loạn Võ: Chọn 2 lá không cùng loại trên tay để bỏ.",

    ["@trick-show"] = "Có thể mở 1 tướng để [%arg] có thêm hiệu ứng.",
    ["trick_show:show_head"] = "Mở chủ tướng",
    ["trick_show:show_deputy"] = "Mở phó tướng",

    ["#simazhao"] = "Trào Phong Khai Thiên",
    ["simazhao"] = "Tư Mã Chiêu",
    ["suzhi"] = "Túc Trí",
    [":suzhi"] = "Tỏa định kỹ:\n• Giới hạn ba lần trong lượt của bạn đối với các mục sau:\n- Khi bạn gây sát thương cho mục tiêu của [Sát] hoặc [Quyết Đấu], bạn lệnh số sát thương +1;\n- Khi bạn sử dụng công cụ không chuyển hóa, bạn rút 1 lá;\n- Sau khi bài của người khác tiến vào chồng bài bỏ do bỏ đi, bạn thu lấy 1 lá của họ.\n• Nếu chưa phát động »Túc Trí« 3 lần trong lượt:\n- Bạn có thể sử dụng công cụ không chuyển hóa không giới hạn khoảng cách;\n- Khi kết thúc lượt chơi, bạn nhận kỹ năng »Phản Quỹ« đến khi bắt đầu lượt tiếp theo của bạn.",
    ["zhaoxin"] = "Chiêu Tâm",
    [":zhaoxin"] = "Sau khi bạn nhận sát thương, bạn có thể mở tất cả bài trên tay, sau đó hoán đổi bài trên tay với 1 người khác không nhiều bài hơn bạn.",
    ["@zhaoxin-exchange"] = "Chiêu Tâm: Chọn 1 người có bài trên tay không nhiều hơn bạn để đổi bài.",
    ["fankui_simazhao"] = "Phản Quỹ",
    
    ["#xuyou"] = "Tất Phương Kiểu Dực",
    ["xuyou"] = "Hứa Du",

    ["chenglve"] = "Thành Lược",
    [":chenglve"] = "Sau khi kết toán bài do 1 người cùng thế lực với bạn sử dụng, nếu số mục tiêu > 1, bạn có thể lệnh họ rút 1 lá;\n‣ Nếu bạn đã nhận sát thương từ lá này, bạn có thể lệnh 1 người cùng thế lực với bạn không có tướng úp và không có tiêu ký nào nhận được 1 tiêu ký [Âm Dương Ngư].",
    ["shicai"] = "Thị Tài",
    [":shicai"] = "Tỏa định kỹ: Sau khi bạn nhận sát thương, nếu số sát thương là:\n- 1: Bạn rút 1 lá;\n- 2+: Bạn bỏ 2 lá.",

    ["@chenglve-mark"] = "Thành Lược: Chọn 1 người nhận tiêu ký [Âm Dương Ngư].",

    ["#xiahouba"] = "Cức Đồ Tráng Chí",
    ["xiahouba"] = "Hạ Hầu Bá",
    ["baolie"] = "Báo Liệt",
    [":baolie"] = "Tỏa định kỹ:\n• Khi bắt đầu giai đoạn ra bài, lệnh những người thế lực xác định khác bạn có tầm đánh đến bạn sử dụng [Sát] với bạn, nếu không, bạn bỏ 1 lá của họ.\n• Bạn sử dụng [Sát] với người có máu ≥ bạn không giới hạn khoảng cách và số lần.",
    ["@baolie-slash"] = "Báo Liệt: Sử dụng [Sát] với %src, hoăc họ bỏ 1 lá của bạn.",

    ["#zhugeke"] = "Hưng Gia Xích Tộc",
    ["zhugeke"] = "Gia Cát Khác",
    ["aocai"] = "Ngạo Tài",
    [":aocai"] = "Ngoài lượt của bạn, khi bạn cần sử dụng hoặc đánh ra bài cơ bản, bạn có thể xem hai lá trên đầu chồng bài, bạn có thể sử dụng hoặc đánh ra lá cơ bản có tên tương ứng trong đó.",
    ["duwu"] = "Độc Võ",
    [":duwu"] = "Hạn định kỹ: Giai đoạn ra bài, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Bạn chọn 1 [Quân Lệnh], yêu cầu tất cả người thế lực khác bạn chấp hành [Quân Lệnh] này; nếu họ không chấp hành, bạn gây 1 sát thương cho họ và rút một lá;\n- Nếu có người thoát khỏi trạng thái hấp hối do nhận sát thương từ kỹ năng này, bạn mất 1 máu.",
    
    ["#aocai"] = "Ngạo Tài",
    ["@aocai-view"] = "Ngạo Tài: Chọn 1 lá phù hợp để sử dụng/đánh ra",

    ["#sunchen"] = "Thực Tủy Đích Triêu Đường Khách",
    ["sunchen"] = "Tôn Lâm",
    ["shilu"] = "Thị Lực",
    [":shilu"] = "\n• Khi có người trận vong, có thể đặt tất cả tướng của họ lên tướng này, gọi là [Lục], nếu họ bị bạn giết, bạn nhận 2 lá từ chồng bài tướng đặt lên tướng này, gọi là [Lục].\n• Khi bắt đầu giai đoạn chuẩn bị, nếu bạn có [Lục], bạn có thể bỏ tối đa X lá (X là số [Lục]), sau đó rút số lá tương ứng.",
    ["xiongnve"] = "Hung Ngược",
    [":xiongnve"] = "\n• Khi bắt đầu giai đoạn ra bài, bạn có thể bỏ 1 [Lục], chọn 1 mục có hiệu quả trong lượt này:\n1. Khi bạn gây sát thương cho người cùng thế lực với [Lục] đã bỏ, sát thương này +1;\n2. Khi bạn gây sát thương cho người cùng thế lực với [Lục] đã bỏ, thu lấy 1 lá của họ;\n3. Bạn sử dụng bài với mục tiêu cùng thế lực với [Lục] đã bỏ không giới hạn số lần.\n• Khi kết thúc giai đoạn ra bài, bạn có thể bỏ 2 [Lục], đến khi bắt đầu lượt tiếp theo của bạn, khi bạn tính toán sát thương phải nhận từ người khác, sát thương này -1. ",

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

	["xiongnve:attack"] = "Có thể phát động »Hung Ngược«, bỏ 1 [Lục] để có hiệu quả tương ứng với thế lực đó",	
	["xiongnve:defence"] = "Có thể phát động »Hung Ngược«, bỏ 2 [Lục] để lệnh sát thương nhận được -1",

    ["#panjun"] = "Quan Nhân Vu Vy",
    ["panjun"] = "Phan Tuấn",
    ["congcha"] = "Quan Vy",
    [":congcha"] = "\n• Khi bắt đầu giai đoạn chuẩn bị, bạn có thể chọn 1 người không có thế lực;\n‣ Cho đến khi bắt đầu lượt tiếp theo của bạn, khi họ mở tướng và trở thành có thế lực, nếu của họ và bạn:\n- Cùng thế lực: Bạn và họ rút 2 lá;\n- Khác thế lực: Họ mất 1 máu.\n• Giai đoạn rút bài, nếu không có người không có thế lực, bạn có thể lệnh số lá rút +2.",
    ["gongqing"] = "Công Thanh",
    [":gongqing"] = "Tỏa định kỹ:\n• Khi bạn tính toán sát thương phải nhận, nếu tầm đánh của nguồn sát thương lớn hơn 3, sát thương này +1;\n• Khi bạn nhận sát thương, nếu tầm đánh của nguồn sát thương nhỏ hơn 3 và sát thương lớn hơn 1, sát thương này trở thành 1.",
    ["@congcha-target"] = "Có thể phát động »Quan Vy«, chọn 1 người không có thế lực.",
    
    ["#congcha-effect"] = "Quan Vy",

    
    ["#wenqin"] = "Dương Châu Thích Sử",
    ["wenqin"] = "Văn Khâm",
    ["jinfa"] = "Căng Phạt",
    [":jinfa"] = "Một lần trong giai đoạn ra bài, có thể bỏ 1 lá và chọn 1 người khác có bài, họ chọn 1 mục:\n1. Lệnh bạn lấy 1 lá của họ;\n2. Họ giao 1 lá trang bị cho bạn, nếu bạn nhận được lá ♠ và lá đó còn trên tay bạn, xem như họ sử dụng 1 [Sát] với bạn.",
    ["@jinfa-give"] = "Căng Phạt: Chọn 1 trang bị giao cho %src hoặc bấm hủy và lệnh %src lấy 1 lá của bạn.",


    ["#huangzu"] = "Giang Hạ Phúc Tâm",
    ["huangzu"] = "Hoàng Tổ",
    ["xishe"] = "Vãn Cung",
    [":xishe"] = "\n• Khi bắt đầu giai đoạn chuẩn bị của người khác, bạn có thể bỏ 1 lá trong vùng trang bị và xem như sử dụng 1 [Sát] với họ không giới hạn khoảng cách, nếu số máu của họ nhỏ hơn của bạn, tất cả người chơi không thể hưởng ứng [Sát] này; bạn có thể lặp lại quá trình này.\n• Khi kết thúc lượt này, nếu trong lượt người trận vong và nguồn là [Sát] từ kỹ năng này của bạn, bạn có thể đổi phó tướng, tướng sau khi đổi được úp xuống.",
    ["@xishe-slash"] = "Có thể phát động »Văn Cung«, bỏ 1 lá trong vùng trang bị, xem như sử dụng [Sát] với %src",
    
    ["#xishe-transform"] = "Vãn Cung",
    
    
    
    ["#gongsunyuan"] = "Giáo Đồ Huyền Hải",
    ["gongsunyuan"] = "Công Tôn Uyên",
    ["huaiyi"] = "Hoài Dị",
    [":huaiyi"] = "\n• Một lần trong giai đoạn ra bài, bạn có thể mở toàn bộ bài trên tay, nếu có đủ 2 màu, bạn thực hiện lần lượt:\n- Bạn chọn 1 màu và bỏ những lá trên tay có màu này;\n- Bạn chọn tối đa X người có bài, thu lấy 1 lá của họ (X là số lá bạn vừa bỏ), nếu lá được thu lấy là trang bị thì đặt lá đó lên tướng này thay vì thu lấy, gọi là [Dị].\n• Bạn có thể sử dụng hoặc đánh ra [Dị] như bài trên tay.",
    ["zisui"] = "Tứ Tuy",
    [":zisui"] = "Tỏa định kỹ:\n• Giai đoạn rút bài, nếu có [Dị], bạn rút thêm X lá (X là số [Dị]).\n• Khi bắt đầu giai đoạn kết thúc, nếu số [Dị] > giới hạn máu của bạn, bạn trận vong.",
    
    ["@huaiyi-choose"] = "Hoài Dị: Chọn 1 màu để bỏ bài",
    ["@huaiyi-snatch"] = "Hoài Dị: Chọn tối đa %arg người, lần lượt thu lấy 1 lá của họ.",
    ["huaiyi:red"] = "Đỏ",
    ["huaiyi:black"] = "Đen",
    
    ["&disloyalty"] = "Di",

	["#test"] = "%arg",
	
	["#pengyang"] = "Giang Dương Thái Thú",
	["pengyang"] = "Bành Dạng",
	
	

    ["tongling"] = "Thông Linh",
    [":tongling"] = "Một lần trong giai đoạn ra bài, sau khi bạn gây sát thương cho 1 người thế lực xác định khác bạn (A), bạn có thể chọn 1 người cùng thế lực với bạn (B), B có thể sử dụng 1 lá với A; sau đó:\n- Nếu lá này gấy sát thương, bạn và B rút 2 lá;\n- Nếu lá này không gây sát thương, bạn lệnh A thu lấy lá bạn đã sử dụng để gây sát thương cho A.",
    ["jinxian"] = "Cận Hãm",
    [":jinxian"] = "Sau khi bạn mở tướng này, bạn lệnh tất cả người trong khoảng cách 1 thực hiện:\n- Nếu họ đã mở tất cả tướng, họ úp 1 tướng\n- Nếu họ có tướng đang úp, họ bỏ 2 lá.",
    
    
    ["@tongling-invoke"] = "Có thể phát động »Thông Linh«, chọn 1 người sử dụng bài lên %dest",
    ["@tongling-usecard"] = "Thông Linh: Chọn 1 lá bài để sử dụng lên %dest",
    ["@jinxian-hide"] = "Cận Hãm: chọn ẩn 1 tướng của bạn",
    ["jinxian_hide:head"] = "Chủ tướng",
    ["jinxian_hide:deputy"] = "Phó tướng",

	
	["#sufei"] = "Hùng Mãnh Dật Tài",
	["sufei"] = "Tô Phi",
	["lianpian"] = "Liên Phiên",
	[":lianpian"] = "Khi bắt đầu giai đoạn kết thúc của 1 người, nếu trong lượt này tổng số bài họ đã bỏ của tất cả người chơi > số máu của bạn, nếu lượt này là lượt của:\n- Bạn: Bạn có thể lệnh 1 người cùng thế lực với bạn bổ sung bài trên tay đến giới hạn máu của họ;\n- Người khác: Họ có thể chọn bỏ 1 lá của bạn hoặc lệnh bạn hồi 1 máu.",
	
	["@lianpian-target"] = "Có thể phát động »Liên Phiên«, chọn 1 người bổ sung bài trên tay đến giới hạn máu",
	["@lianpian"] = "Có thể phát động »Liên Phiên« của %src",
	["#lianpian-other"] = "Liên Phiên",
	["lianpian:discard"] = "Bỏ 1 lá của họ.",
	["lianpian:recover"] = "Lệnh họ hồi 1 máu.",
	
	["#liuba"] = "Sắc Hành Chỉnh Thân",
	["liuba"] = "Lưu Ba",
	["tongdu"] = "Trù Độ",
	[":tongdu"] = "Khi bắt đầu giai đoạn kết thúc của người cùng thế lực với bạn, họ có thể rút X lá (X là số bài họ đã bỏ trong giai đoạn bỏ bài ở lượt này, tối đa 3).",
	["qingyin"] = "Quy Ẩn",
	[":qingyin"] = "Hạn định kỹ: Giai đoạn ra bài, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Lệnh tất cả người cùng thế lực với bạn hồi đầy máu;\n- Bạn loại bỏ tướng này.",
	["@tongdu"] = "Có thể phát động »Trù Độ« của %src",
	["#tongdu-other"] = "Trù Độ",
	
	["#zhuling"] = "Kiên Thành Túc Tướng",
	["zhuling"] = "Chu Linh",
	["juejue"] = "Trấn Vệ",
	[":juejue"] = "\n• Khi bắt đầu giai đoạn bỏ bài, bạn có thể mất 1 máu; Nếu làm vậy, khi kết thúc giai đoạn này, nếu trong giai đoạn này bạn có bỏ bài, bạn lệnh tất cả người khác chọn 1 mục:\n1. Họ đưa X lá trên tay vào chồng bài bỏ (X là số lá bạn đã bỏ trong giai đoạn này);\n2. Bạn gây 1 sát thương cho họ.\n• Khi bạn giết người cùng thế lực với bạn, bạn bỏ qua chấp hành thưởng phạt.",
	["fangyuan"] = "Ngư Lân",
	[":fangyuan"] = "Trận pháp kỹ: Quan hệ vây công:\n• Nếu bạn là người vây công, giới hạn trữ bài của người vây công +1, giới hạn trữ bài của người bị vây công -1.\n• Khi bắt đầu giai đoạn kết thúc, nếu bạn là người bị vây công trong quan hệ vây công, bạn xem như sử dụng [Sát] với 1 người vây công",
	["@fangyuan-slash"] = "Ngư Lân: chọn 1 người đang vây công bạn, xem như sử dụng [Sát] với họ",
	
	["@juejue-discard"] = "Trấn Vệ: Bỏ %arg lá trên tay, hoặc %src gây 1 sát thương với bạn.",
	
	["#fangyuan-maxcards"] = "Ngư Lân",


}
