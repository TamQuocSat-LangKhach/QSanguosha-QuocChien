joy = sgs.Package("joy",sgs.Package_CardPack, true)												

shit = sgs.CreateBasicCard{		
	name = "shit",	
	-- objectName của lá bài này	
	class_name = "Shit",	
	-- Class name của lá bài này.	
	-- Đối với lá bài, chúng ta thường tương tác với class nhiều hơn là name	
	-- Do đó việc có Class name là bắt buộc	
	subtype = "disgusting_card",	
	-- Phân loại nhỏ của lá bài, chỉ sử dụng để hiển thị trong Wiki in game	
	can_recast = false,	
	-- Lá này không thể Trùng Chú	
	target_fixed = true,	
	-- Lá bài này sử dụng không cần lựa chọn mục tiêu	
	-- Mục tiêu mặc định là bản thân khi set như thế này	
	on_effect = function(self,effect)	
		return false
		-- Lá bài này không có hiệu quả gì khi sử dụng
	end,	
}		

poisonEff = sgs.CreateTriggerSkill{						
-- Tạo 1 trigger skill, là loại kỹ năng phát động theo thời điểm phù hợp						
	name = "poison",					
	-- ObjectName của kỹ năng					
	events = {sgs.CardsMoveOneTime},					
	-- Thời điểm phát động là Sau khi mất lá bài (Sau khi lá bài di chuyển)					
	-- Xem thêm TriggerEvent để hiểu hơn về các timing có trong game					
	frequency = sgs.Skill_Compulsory,					
	-- Loại kỹ năng này xem như tỏa định kỹ					
	global = true,					
	-- Kỹ năng chung của tất cả người chơi					
	on_record = function(self, event, room, player, data)					
	-- on_record là 1 function tự động thực hiện khi đến thời điểm phù hợp.					
	-- Thường chỉ dùng để ghi chép hoặc thực hiện các lệnh không cần hoặc hiếm khi phải hỏi người chơi					
	-- Việc chạy lệnh của on_record không tính là phát động kỹ năng					
		local move_datas = data:toList()				
		-- Loại data tương ứng với sự kiện CardsMoveOneTime là 1 QVariant list kiểu MoveOneTime				
		-- TriggerEvent có chú thích từng timing một tương ứng với loại data gì				
		-- Cần phải lưu ý loại data theo timing, việc convert sai sẽ dẫn tới crash game				
		for _, move_data in sgs.qlist(move_datas) do				
		-- Đối với List có kiểu QVariantList, thường được lấy từ hàm data:toList()				
		-- Chúng ta sử dụng sgs.qlist để convert về list tiêu chuẩn, dùng lệnh for trên để duyệt,				
			local move = move_data:toMoveOneTime()			
			-- move_data lấy ra từ list trên đang có kiểu là QVariant, cần phải convert về MoveOneTime			
			if not move.from or move.from:objectName() ~= player:objectName() then			
				continue		
				-- Sự kiện mất bài sẽ trigger với tất cả người chơi		
				-- Do đó, cần phải check người đang được trigger có phải là người mất bài không		
				-- Xem thêm trigger event để biết từng event sẽ trigger với những người nào		
			end			
			if move.to_place ~= sgs.Player_PlaceTable or move.to_place ~= sgs.DiscardPile then			
				continue		
				-- Theo text, di chuyển lên sân hoặc chồng bài bỏ mới kích		
			end			
			local shit_list = {}			
			local i = 0			
			for _, card_str in pairs(move.cards) do			
				local card = sgs.Card_Parse(card_str)		
				if card and card:isKindOf("Shit") and move.from_places:at(i) == sgs.Player_PlaceHand then		
				-- Kiểm tra lá bị mất lần này có phải là Thỉ và đến từ tay người chơi không		
				-- isKindOf sẽ kiểm tra theo Class name, đó là lí do cần phải khai báo class với lá bài		
					table.insert(shit_list, card:getId())	
				end		
				i = i + 1		
			end			
			if #shit_list == 0 then			
				continue		
				-- Không có thỉ bị mất thì bỏ qua		
			end			
			if #shit_list > 1 then			
				local arrangeData = room:askForArrangeCards(player, shit_list, sgs.Room_GuanxingUpOnly)		
				shit_list = arrangeData.top		
				-- Nếu có từ 2 Thỉ trở lên bị mất, yêu cầu người chơi sắp xếp thứ tự phát động		
			end			
			for _, shit_id in ipairs(shit_list) do			
				if (player:isDead()) then		
					break	
				end		
				local card = sgs.Sanguosha:getCard(shit_id)		
				local log = sgs.LogMessage()		
				log.card_str = card:toString()		
				log.from = player		
				log.type = "$ShitDamage"		
				if card:getSuit() == sgs.Card_Spade then		
					log.type = "$ShitLostHp"	
					room:sendLog(log)	
					room:loseHp(player)	
				elseif card:getSuit() == sgs.Card_Heart then		
					log.arg = "fire_nature"	
					room:sendLog(log)	
					room:damage(sgs.DamageStruct(card, nil, player, 1, sgs.DamageStruct_Fire))	
				elseif card:getSuit() == sgs.Card_Club then		
					log.arg = "thunder_nature"	
					room:sendLog(log)	
					room:damage(sgs.DamageStruct(card, nil, player, 1, sgs.DamageStruct_Thunder))	
				elseif card:getSuit() == sgs.Card_Diamond then		
					log.arg = "normal_nature"	
					room:sendLog(log)	
					room:damage(sgs.DamageStruct(card, nil, player))	
				end		
			end			
		end				
	end,					
}						