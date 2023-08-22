CardUseStruct = {
	-- Struct này được sử dụng trong các timing liên quan đến quá trình sử dụng lá bài.
	-- sử dụng data:toCardUse() để chuyển từ data sang CardUseStruct.
	-- sử dụng local cardUse = sgs.CardUseStruct() để tạo struct.

	card, -- Trả về lá bài đang được sử dụng.
    from, -- Trả về 1 player, là người sử dụng bài.
	to, -- Trả về list player, là những mục tiêu của lá này
	index, -- Kiểu int, trả về index của mục tiêu đang giải quyết timing, thường dùng trong timing Sau khi xác định mục tiêu của lá bài. sử dụng to.at(index) để lấy ra mục tiêu đang cần giải quyết ở timing này. với những kỹ năng chỉ phát động 1 lần sau khi xác định tất cả mục tiêu (tôn sách) thì cần check index = 0.
	m_addHistory, -- Kiểu bool, nếu false thì lá đang sử dụng không bị tính vào số lần đã sử dụng cho lượt. Thường áp dụng cho tất cả kỹ năng xem như sử dụng sát
	m_isHandcard, -- Kiểu bool, nếu true thì lá này vốn là lá trên tay
	m_isOwnerUse, -- Kiểu bool, nếu true thì lá này vốn là của người sử dụng. Nếu bạn muốn tạo 1 kỹ năng mà dùng bài của người khác thì hay để giá trị này là false
	m_reason, -- Lý do sử dụng lá này. Hiện quốc chiến chưa có kỹ năng sử dụng. Các giá trị:
		-- sgs.CardUseStruct_CARD_USE_REASON_PLAY: Sử dụng khi đang rảnh trong giai đoạn ra bài
		-- sgs.CardUseStruct_CARD_USE_REASON_RESPONSE_USE: Sử dụng do hưởng ứng tình huống cụ thể, ví dụ Thiểm, Vô Giải, Đào Tửu cứu hấp hối, Thông Linh Bành Dạng...

	nullified_list, -- Trả về list string, chứa objectName của những người không còn nhận hiệu quả của lá này. bạn có thể add objectName() của player vào list này để vô hiệu với người đó, VD Lưu Thiện.

	disresponsive_list, -- Trả về list string, chứa objectName của những người không được hưởng ứng với lá này. nếu list có chứa "_ALL_PLAYERS" thì tất cả người chơi không thể hưởng ứng. Bạn cũng có thể add thông tin vào list này để khiến những người trong này không thể hưởng ứng.
}
