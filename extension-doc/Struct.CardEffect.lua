CardEffectStruct = {
	-- Struct này được sử dụng trong các timing liên quan đến quá trình giải quyết hiệu quả lá bài.
	-- sử dụng data:toCardEffect() để chuyển từ data sang CardEffectStruct
	-- sử dụng local cardEffect = sgs.CardEffectStruct() để tạo struct, thường dùng để vô hiệu hoặc ngăn hưởng ứng trong lúc giải quyết hiệu quả.

    from, -- Trả về 1 player, là người sử dụng bài. Có thể null
	to, -- Trả về 1 player, là người đang giải quyết hiệu quả lá bài
	card, -- Trả về lá bài đang có hiệu quả.
    multiple, -- Kiểu bool, true nghĩa là lá đang giải quyết là đa mục tiêu
    nullified, -- Kiểu bool, true nghĩa là lá này đã bị vô hiệu. Thường chỉ dùng cho vô giải.
	disresponsive, -- Kiểu bool, true nghĩa là hiệu quả này không thể hưởng ứng bởi tất cả người chơi
}
