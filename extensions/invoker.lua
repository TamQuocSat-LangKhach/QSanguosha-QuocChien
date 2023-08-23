extension = sgs.Package("dota", sgs.Package_GeneralPack, true)

invoker = sgs.General(extension, "invoker", "qun", 3, true) 

sgs.LoadTranslationTable{
	["#invoker"] = "Kì Cầu Giả",
	["invoker"] = "Invoker",
	["designer:invoker"] = "Lãng Khách",
	["illustrator:invoker"] = "",
	["cv:invoker"] = "",
	["element"] = "Nguyên Tố",
	[":element"] = "• Giai đoạn ra bài hoặc sau khi 1 người bắt đầu lượt, bạn có thể bỏ 1 lá có trong danh sách dưới đây và nhận hiệu quả tương ứng:\n"..
	"* [Sát] phổ thông, [Quyết Đấu], [Hàn Băng Kiếm]: Bạn nhận 1 điểm nguyên tố [Băng];\n"..
	"* [Sát Lôi], [Thủy Yêm Thất Quân], [Thiểm Điện]: Bạn nhận 1 điểm nguyên tố [Lôi];\n"..
	"* [Sát Hỏa], [Hỏa Công], [Hỏa Thiêu Liên Doanh], [Chu Tước Vũ Phiến]: Bạn nhận 1 điểm nguyên tố [Hỏa];\n"..
	"▷ Nếu tổng số điểm nguyên tố của bạn là 4, bạn bỏ đi điểm nguyên tố đầu tiên đã nhận được.\n"..
	"• Tỏa định kỹ: Khi bắt đầu giai đoạn chuẩn bị, nếu bạn có 3 nguyên tố giống nhau và nguyên tố đó là:\n"..
	"* [Băng]: Bạn hồi 1 máu;\n"..
	"* [Lôi]: Trong lượt này, bạn sử dụng bài không hạn chế khoảng cách;\n"..
	"* [Hỏa]: Nếu bạn thỏa mãn điều kiện sử dụng [Tửu], xem như bạn sử dụng 1 [Tửu]."..
	
	["invoke"] = "Kì Hoán",
	[":invoke"] "Giai đoạn ra bài hoặc sau khi 1 người bắt đầu lượt, nếu bạn có 3 nguyên tố, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Nếu kỹ năng ứng với tổ hợp nguyên tố của bạn khác với kỹ năng bạn đã có, bạn nhận kỹ năng đó đến khi bạn mất kỹ năng này;\n- Nếu bạn có 3 kỹ năng đã được nhận bởi kỹ năng này, bạn mất kỹ năng đã nhận đầu tiên.",

	["coldsnap"] = "Lãnh Khước",
	[":coldsnap"] = "Băng-Băng-Băng\nMột lần trong giai đoạn ra bài, bạn có thể bỏ 1 lá và chọn 1 người khác, lệnh họ nhận 1 ký hiệu [Lãnh Khước] đến khi bắt đầu lượt tiếp theo của bạn;\n▶ Sau khi 1 người xác định mục tiêu của lá [Sát], ứng với mỗi mục tiêu, nếu mục tiêu này có [Lãnh Khước], họ thực hiện lần lượt:\n- Người sử dụng [Sát] có thể sử dụng 1 lá RÔ như [Lạc Bất Tư Thục] với họ;\n- Họ không thể hưởng ứng [Sát] này;\n- Loại bỏ [Lãnh Khước].",
	
	["ghostwalk"] = "U Linh",
	[":ghostwalk"] = "Băng-Băng-Lôi\nTỏa định kỹ:\n• Khoảng cách từ người khác đến bạn +2.\n• Khoảng cách từ bạn đến người khác -1.\n• Khi bạn trở thành mục tiêu của công cụ đơn mục tiêu do người khác sử dụng, nếu bạn không trong tầm đánh của họ, hủy bỏ mục tiêu đối với bạn.\n• Giai đoạn rút bài, bạn rút +1 lá.",
	
	["icewall"] = "Băng Tường",
	[":icewall"] = "Băng-Băng-Hỏa\nTrận pháp kỹ: Quan hệ đội hình: Nếu bạn có trong quan hệ đội hình:\n• Người cùng đội hình với bạn nhận kỹ năng »Phi Ảnh« và »Cương Liệt«.",
	
	["emp"] = "Từ Xung",
	[":emp"] = "Lôi-Lôi-Lôi\nMột lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá thành [Thủy Yêm Thất Quân];\n▶ Khi bạn sử dụng lá này, nếu họ đã mở tất cả tướng, bạn úp 1 tướng của họ, trong lượt này họ không thể mở tướng này;\n▶ Sau khi kết toán xong lá này, bạn rút 1 lá.",
	
	["tornado"] = "Cụ Phong",
	[":tornado"] = "Băng-Lôi-Lôi\nMột lần trong giai đoạn ra bài, bạn có thể bỏ 1 lá và chọn 1 người ngồi cạnh bạn, lệnh người cùng đội hình với họ thực hiện lần lượt:\n- Họ chọn 1 lá trên tay và bỏ đi những lá trên tay còn lại;\n- Nếu họ không bỏ lá đỏ, bạn gây 1 sát thương Lôi cho họ.",
	
	["alacrity"] = "Tấn Thiệp",
	[":alacrity"] = "Lôi-Lôi-Hỏa\nKhi bắt đầu giai đoạn hành động của người cùng thế lực với bạn, bạn có thể bỏ 1 lá, lệnh họ +1 giới hạn sử dụng [Sát] trong giai đoạn này",
	
	["sunstrike"] = "Dương Diễm",
	[":sunstrike"] = "Hỏa-Hỏa-Hỏa\nMột lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá thành [Hỏa Công];\n▷ Sát thương từ [Hỏa Công] này +1.",
	
	["forgespirit"] = "Dung Linh",
	[":forgespirit"] = "Băng-Hỏa-Hỏa\nTỏa định kỹ:\n• Khi tính toán số người cùng đội hình với bạn, +1 giá trị này.\n• Sau khi kết toán xong [Sát] đầu tiên bạn sử dụng trong giai này, xem như bạn sử dụng 1 [Sát Hỏa].",
	
	["chaosmeteor"] = "Hỗn Thạch",
	[":chaosmeteor"] = "Lôi-Hỏa-Hỏa\nMột lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá thành [Hỏa Thiêu Liên Doanh] bỏ qua phòng cụ của mục tiêu, mục tiêu của lá này không thể hưởng ứng.",

	["deafeningblast"] = "Siêu Thanh",
	[":deafeningblast"] = "Băng-Lôi-Hỏa\nMột lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá thành [Sát] bỏ qua phòng cụ của mục tiêu và giới hạn sử dụng [Sát];\n▶ Sau khi bạn gây sát thương cho mục tiêu của [Sát] này, lệnh họ không thể sử dụng [Sát] cho đến sau khi kết thúc lượt tiếp theo của họ.",
}
	
return {extension}