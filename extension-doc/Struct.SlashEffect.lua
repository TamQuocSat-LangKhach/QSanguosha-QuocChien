SlashEffectStruct = {
	-- Struct này được sử dụng trong các timing liên quan đến quá trình giải quyết hiệu quả lá Sát.
	-- sử dụng data:toSlashEffect() để chuyển từ data sang SlashEffectStruct
	-- sử dụng local slashEffect = sgs.SlashEffectStruct() để tạo struct

    from, -- Trả về 1 player, là người sử dụng bài.
	to, -- Trả về 1 player, là người đang giải quyết hiệu quả lá Sát
	slash, -- Trả về lá Sát đang có hiệu quả.
	jink, -- Trả về lá Thiểm đã triệt tiêu Sát này. Nếu sát này cần sử dụng nhiều thiểm để triệt tiêu, chỉ lưu thiểm cuối cùng, lá mà có hiệu quả triệt tiêu Sát
    jink_num, -- Kiểu int, là số Thiểm mà mục tiêu cần sử dụng để triệt tiêu
    drank, -- Kiểu int, là số Tửu đang có hiệu quả với Sát này.
	nature, -- Thuộc tính của lá sát này. Xem thêm Struct.Damage.lua để biết thêm.
	nullified, -- Kiểu bool, true có nghĩa sát này đã bị vô hiệu
	
}
