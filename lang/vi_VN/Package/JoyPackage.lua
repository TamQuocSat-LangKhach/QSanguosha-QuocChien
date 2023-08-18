-- translation for JoyPackage

return {
	["joy"] = "Hoan Lạc",

	["shit"] = "Thỉ",
	[":shit"] = "Bài cơ bản\n\n<b>Thời điểm</b>: Giai đoạn ra bài\n<b>Mục tiêu</b>: Bạn\n<b>Hiệu quả</b>: Không có\n\n<b>Hiệu ứng thêm</b>: Trong lượt của bạn, khi lá này từ tay của bạn tiến vào chồng bài bỏ hoặc bàn chơi, nếu chất của lá này là:\n* BÍCH: Bạn mất 1 máu;\n* TÉP: Bạn nhận 1 sát thương Lôi;\n* RÔ: Bạn nhận 1 sát thương;\n* CƠ: Bạn nhận 1 sát thương Hỏa.",
	["disgusting_card"] = "Lá bốc mùi",
	["$ShitLostHp"] = "%from đã ăn %card, mất 1 máu",
	["$ShitDamage"] = "%from đã ăn %card, nhận 1 sát thương.",

-- disaster
	["Disaster"] = "Thiên Tai",

	["deluge"] = "Hồng Thủy",
	[":deluge"] = "Bài công cụ thời gian\n\n<b>Mục tiêu</b>: Bạn\n<b>Hiệu quả</b>: Giai đoạn phán xét của mục tiêu, tiến hành phán xét, nếu kết quả phán xét có điểm là:\n* A/K: Thực hiện lần lượt:\n- Mục tiêu ngẫu nhiên mở ra số bài của họ bằng số người còn sống;\n- Những người khác thu lấy 1 lá từ số bài này;\n- Đưa [Hồng Thủy] này vào chồng bài bỏ;\n* Ngược lại: [Hồng Thủy] chuyển sang vùng phán xét của người tiếp theo.",

	["typhoon"] = "Đài Phong",
	[":typhoon"] = "Bài công cụ thời gian\n\n<b>Mục tiêu</b>: Bạn\n<b>Hiệu quả</b>: Giai đoạn phán xét của mục tiêu, tiến hành phán xét, nếu kết quả phán xét:\n* Từ 2~9 RÔ: Những người ở khoảng cách 1 của mục tiêu bỏ 6 lá trên tay; đưa [Đài Phong] này vào chồng bài bỏ;\n* Ngược lại: [Đài Phong] chuyển sang vùng phán xét của người tiếp theo.",

	["earthquake"] = "Địa Chấn",
	[":earthquake"] = "Bài công cụ thời gian\n\n<b>Mục tiêu</b>: Bạn\n<b>Hiệu quả</b>: Giai đoạn phán xét của mục tiêu, tiến hành phán xét, nếu kết quả phán xét:\n* Từ 2~9 TÉP: Những người ở khoảng cách 1 của mục tiêu (bỏ qua hiệu ứng từ ngựa +1) bỏ tất cả trang bị; đưa [Địa Chấn] này vào chồng bài bỏ;\n* Ngược lại: [Địa Chấn] chuyển sang vùng phán xét của người tiếp theo.",

	["volcano"] = "Hỏa Sơn",
	[":volcano"] = "Bài công cụ thời gian\n\n<b>Mục tiêu</b>: Bạn\n<b>Hiệu quả</b>: Giai đoạn phán xét của mục tiêu, tiến hành phán xét, nếu kết quả phán xét:\n* Từ 2~9 CƠ: Mục tiêu nhận 2 sát thương Hỏa, những người ở khoảng cách 1 của mục tiêu (bỏ qua hiệu ứng từ ngựa +1) nhận 1 sát thương Hỏa; đưa [Hỏa Sơn] này vào chồng bài bỏ;\n* Ngược lại: [Hỏa Sơn] chuyển sang vùng phán xét của người tiếp theo.",

	["mudslide"] = "Nễ Thạch Lưu",
	[":mudslide"] = "Bạn\n<b>Hiệu quả</b>: Giai đoạn phán xét của mục tiêu, tiến hành phán xét, nếu kết quả phán xét:\n* Màu Đen và điểm là A/K/4/7: Thực hiện lần lượt:\n- Mỗi người nếu không có lá trong vùng trang bị, họ nhận 1 sát thương; ngược lại, họ bỏ bài trong vùng trang bị nhiều nhất có thể, tối đa tổng 4 lá trang bị bị bỏ từ tất cả mọi người, ưu tiên theo thứ tự Vũ khí, Phòng cụ, Ngựa +1, Ngựa -1, Bảo vật, Ngựa đặc biệt;\n▷ Nếu tổng số trang bị đã bị bỏ bởi [Nễ Thạch Lưu] là 4, ngưng kết toán với những người còn lại\n- Đưa [Nễ Thạch Lưu] này vào chồng bài bỏ;\n* Ngược lại: [Nễ Thạch Lưu] chuyển sang vùng phán xét của người tiếp theo.",

-- equips
	["JoyEquip"] = "Hoan Lạc - Trang Bị",

	["monkey"] = "Hầu Tử",
	[":monkey"] = "Bài trang bị - Chiến Mã\n\nKỹ năng:\n" ..
	"Khi người khác sử dụng [Đào], bạn có thể bỏ [Hầu Tử], loại bỏ mục tiêu của lá [Đào] này và thu lấy lá đó.\nTỏa định kỹ, khoảng cách từ bạn đến người khác -1.",
	["grab_peach"] = "Thu Đào",



	["yx_sword"] = "Dương Tu Kiếm",
	[":yx_sword"] = "Bài trang bị - Vũ khí\n\nTầm đánh: 4\nKỹ năng: Khi lá [Sát] của bạn tạo gây thương, bạn có thể lệnh 1 người khác trong tầm đánh của bạn trở thành nguồn sát thương, sau đó bạn giao [Dương Tu Kiếm] cho họ.",
	["@yxsword-select"] = "Bạn có thể chỉ định 1 người trong tầm đánh trở thành nguồn sát thương",

}
