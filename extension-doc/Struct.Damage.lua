DamageStruct = {
	-- Struct này được sử dụng trong các timing liên quan đến quá trình gây sát thương.
	-- sử dụng data:toDamage() để chuyển từ data sang DamageStruct
	-- sử dụng local damage = sgs.DamageStruct() để tạo struct nếu muốn tạo kỹ năng gây sát thương

    from, -- Trả về 1 player, là nguồn gây sát thương. Có thể null
	to, -- Trả về 1 player, là người nhận sát thương
	card, -- Trả về lá đã gây sát thương. có thể null. lá được trả là lá được tuyên bố sử dụng, có thể là lá gốc, lá chuyển hóa hoặc lá ảo. 
    damage, -- Kiểu int, là số sát thương
    nature, -- Trả về thuộc tính của sát thương. Khi cần kiểm tra nature hoặc set nature, sử dụng các thuộc tính sau:
		--sgs.DamageStruct_Normal
		--sgs.DamageStruct_Fire
		--sgs.DamageStruct_Thunder
	chain, -- Kiểu bool. true có nghĩa đây là sát thương do lan xích.
	transfer, -- Kiểu bool. true có nghĩa đây là sát thương do chuyển sát thương. Chỉ sử dụng ở Tiểu Kiều cũ, hiện không còn sử dụng.
	-- nếu bạn muốn kiểm tra sát thương này được gây cho mục tiêu của lá bài (chúc dung, tam tiên), hãy kiểm tra nếu lá bài đúng loại (sát) và 2 thuộc tính chain và transfer là false.
	by_user, -- Kiểu bool, true có nghĩa sát thương này do chính người sử dụng bài gây ra, false thì không phải (vd mạnh hoạch cướp nguồn, quyết đấu thua). ví dụ Tư Mã Chiêu cần check nếu trong lượt bằng cách nào đó bị quyết đấu nhưng thắng thì sẽ không +1 sát thương.
	
    reason, -- Trả về String. Thường là code name của kỹ năng gây ra sát thương. Khi bạn code 1 kỹ năng gây ra sát thương, hãy set reason = self:objectName() để các kỹ năng khác có thể hoạt động đúng
    flags, -- Trả về 1 StringList. có chứa các flag custom cho mục đích cụ thể. 1 số flag mặc định có sẵn để bạn có thể check nếu phù hợp vỡi kỹ năng của bản thân (Những flag này đc đặt tên theo kỹ năng tướng ứng sử dụng, nhưng bạn vẫn có thể sử dụng ở những kỹ năng khác):
		-- "kuanggu": Sát thương này cho người trong khoảng cách từ 1 trở xuống. Dùng cho cuồng cốt
		-- "zhidao": Sát thương này là sát thương được gây ra lần đầu bởi bạn cho người này trong giai đoạn này. Dùng cho Trĩ Đạo
		-- "zhukou": Sát thương này là sát thương được gây ra lần đầu bởi bạn trong giai đoạn này. Dùng cho Trục Khấu
	-- Bạn cũng có thể tự định nghĩa cờ của riêng mình cho mục đích cụ thể, recommended sử dụng timing PreDamageDone để đánh dấu cờ này.
    transfer_reason, -- Kiểu string, Hiện không còn sử dụng. Nếu bạn làm 1 kỹ năng dạng chuyển sát thương như tiểu kiều cũ, hay set giá trị self:objectName() cho trường này.
	prevented, -- Kiểu bool. Chỉ sử dụng ở timing DamageComplete, true nghĩa là sát thương này đã bị chặn. Bạn có thể định nghĩa 1 kỹ năng sau khi sát thương bị chặn ở timing này

}
