xiliang = sgs.Package("xiliang", sgs.Package_GeneralPack)





sgs.LoadTranslationTable{
    ["xiliang"] = "SP - Dự bị",
}

--建立武将
zhangchunhua = sgs.General(xiliang, "zhangchunhua", "wei", 3, false)
zhangchunhua:addCompanion("simayi")

caoang = sgs.General(xiliang, "caoang", "wei")
caoang:addCompanion("dianwei")


shitao = sgs.General(xiliang, "shitao", "shu")
shitao:addCompanion("wolong")
shitao:addCompanion("xushu")
shitao:setHeadMaxHpAdjustedValue()

--diy_xushu = sgs.General(xiliang, "diy_xushu", "shu")
--diy_xushu:addCompanion("wolong")
--diy_xushu:addCompanion("zhaoyun")
--diy_xushu:addCompanion("shitao")
--diy_xushu:setDeputyMaxHpAdjustedValue()

chengpu = sgs.General(xiliang, "chengpu", "wu")
chengpu:addCompanion("zhouyu")

guyong = sgs.General(xiliang, "guyong", "wu", 3)

gongsunzan = sgs.General(xiliang, "gongsunzan", "qun")
gongsunzan:setHeadMaxHpAdjustedValue()

chengyu = sgs.General(xiliang, "chengyu", "wei", 3)
chengyu:addCompanion("caopi")

guohuai = sgs.General(xiliang, "guohuai", "wei")
guohuai:addCompanion("zhanghe")

--chendao = sgs.General(xiliang, "diy_chendao", "shu")
--chendao:addCompanion("zhaoyun")

maliang = sgs.General(xiliang, "maliang", "shu", 3)
maliang:addCompanion("zhugeliang")


quancong = sgs.General(xiliang, "quancong", "wu")

chendeng = sgs.General(xiliang, "chendeng", "qun", 3)



yijibo = sgs.General(xiliang, "yijibo", "shu", 3)

sunhuan = sgs.General(xiliang, "sunhuan", "wu")
sunhuan:addCompanion("luxun")

zhangyi = sgs.General(xiliang, "zhangyi", "shu")
zhangyi:addCompanion("liaohua")

zhuhuan = sgs.General(xiliang, "zhuhuan", "wu")


















local skills = sgs.SkillList()


--[[******************
    建立一些通用内容
]]--******************
--建立空卡

MemptyCard = sgs.CreateSkillCard{
	name = "MemptyCard",
	target_fixed = true,
}
--建立table-qlist函数
Table2IntList = function(theTable)
	local result = sgs.IntList()
	for _, x in ipairs(theTable) do
		result:append(x)
	end
	return result
end

listIndexOf = function(theqlist, theitem)
	local index = 0
	for _, item in sgs.qlist(theqlist) do
		if item == theitem then return index end
		index = index + 1
	end
end

--建立获取服务器玩家函数
function getServerPlayer(room, name)
	for _, p in sgs.qlist(room:getAllPlayers(true)) do
		if p:objectName() == name then return p end
	end
	return nil
end

function skillTriggerable(player, name)
	return player ~= nil and player:isAlive() and player:hasSkill(name)
end

getKingdoms = function(player, will_show)
	local n = 0
    local kingdom_set = {}
	local allplayers = player:getAliveSiblings()
	local same_kingdom = false
	if will_show and not player:hasShownOneGeneral() then
	    for _, p in sgs.qlist(allplayers) do
	        if player:willBeFriendWith(p) then
		        same_kingdom = true
				break
		    end
	    end
		if not same_kingdom then
	        n = n + 1
	    end
	end
	if not same_kingdom then
	    allplayers:append(player)
	end
	for _, p in sgs.qlist(allplayers) do
		if not p:hasShownOneGeneral() then
			continue
		end
		if p:getRole() == "careerist" then
		    n = n + 1
			continue
		end
		if not table.contains(kingdom_set, p:getKingdom()) then table.insert(kingdom_set, p:getKingdom()) end
	end
	return n + #kingdom_set
end




zhuhai = sgs.CreateTriggerSkill{
	name = "zhuhai" ,
	events = {sgs.EventPhaseStart} ,
	can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		if player and player:isAlive() and player:getPhase() == sgs.Player_Finish and player:getMark("Global_DamagePiont_Round") > 0 then
			local xushus = room:findPlayersBySkillName(self:objectName())
            for _, xushu in sgs.qlist(xushus) do
				if xushu:canSlash(player, false) then
					table.insert(skill_list, self:objectName())
					table.insert(name_list, xushu:objectName())
				end
			end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
	on_cost = function(self, event, room, player, data, xushu)
		local source_data = sgs.QVariant()
		source_data:setValue(player)
		if xushu:askForSkillInvoke(self:objectName(), source_data) then
		    room:broadcastSkillInvoke(self:objectName(), xushu)
			return true
		end
	end,
    on_effect = function(self, event, room, player, data, xushu)
		room:askForUseSlashTo(xushu, player, "@zhuhai:" .. player:objectName(), false)
		return false
	end,
}

pozhen = sgs.CreateTriggerSkill{
	name = "pozhen" ,
	events = {sgs.EventPhaseStart},
	frequency = sgs.Skill_Limited,
	limit_mark = "@pozhen",
	on_record = function(self, event, room, player, data)
		if player:getPhase() == sgs.Player_NotActive then
			room:setPlayerMark(player, "##pozhen", 0)
		end
	end,
	can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		if player and player:isAlive() and player:getPhase() == sgs.Player_Start then
			local xushus = room:findPlayersBySkillName(self:objectName())
            for _, xushu in sgs.qlist(xushus) do
				if xushu ~= player and xushu:getMark("@pozhen") > 0 then
					table.insert(skill_list, self:objectName())
					table.insert(name_list, xushu:objectName())
				end
			end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
	on_cost = function(self, event, room, player, data, xushu)
		local source_data = sgs.QVariant()
		source_data:setValue(player)
		if xushu:askForSkillInvoke(self:objectName(), source_data) then
		    room:broadcastSkillInvoke(self:objectName(), xushu)
			room:doAnimate(1, xushu:objectName(), player:objectName())
			room:doSuperLightbox("xushu", self:objectName())
            room:setPlayerMark(xushu, "@pozhen", 0)
			return true
		end
	end,
    on_effect = function(self, event, room, player, data, xushu)
		room:addPlayerMark(player, "##pozhen")
        room:setPlayerCardLimitation(player, "use,response,recast", ".|.|.|hand", true)
		
		local targets = sgs.SPlayerList()
		local other_players = room:getOtherPlayers(xushu)
		local all_players = room:getAlivePlayers()
		
		local can_discard = false
		
		for _, p in sgs.qlist(other_players) do
			local in_siege_relation = false
			
			for _, p2 in sgs.qlist(all_players) do
				if player:inSiegeRelation(p, p2) then
					in_siege_relation = true
					break
				end
			end
			
			if player:inFormationRalation(p) or in_siege_relation then
                targets:append(p)
                if not p:isNude() then
                    can_discard = true
				end
            end
		end
		
		if can_discard and room:askForChoice(xushu, "pozhen_discard", "yes+no", data, "@pozhen-discard::" .. player:objectName()) == "yes" then
			room:sortByActionOrder(targets)
            for _, p in sgs.qlist(targets) do
                if xushu:canDiscard(p, "he") then
                    room:throwCard(room:askForCardChosen(xushu, p, "he", self:objectName(), false, sgs.Card_MethodDiscard), p, xushu)
                end
            end
		
		end
		return false
	end,
}

jiancai = sgs.CreateTriggerSkill{
	name = "jiancai",
	events = {sgs.DamageInflicted, sgs.GeneralTransforming},
	relate_to_place = "deputy",
    can_trigger = function(self, event, room, player, data)		
		local skill_list = {}
		local name_list = {}
		if event == sgs.DamageInflicted then
			local damage = data:toDamage()
			if damage.damage < player:getHp() then
				return "", ""
			end
		end
		local xushus = room:findPlayersBySkillName(self:objectName())
        for _, xushu in sgs.qlist(xushus) do
			if xushu:isFriendWith(player) then
				table.insert(skill_list, self:objectName())
				table.insert(name_list, xushu:objectName())
			end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
		
	end,
	on_cost = function(self, event, room, player, data, xushu)
		if event == sgs.DamageInflicted then
			xushu:setTag("JiancaiDamagedata", data)
			local invoke = xushu:askForSkillInvoke(self, sgs.QVariant("damage::" .. player:objectName()))
			xushu:removeTag("JiancaiDamagedata")
			if invoke then
				room:broadcastSkillInvoke(self:objectName(), xushu)
				room:doAnimate(1, xushu:objectName(), player:objectName())
				return true
			end
		end
		if event == sgs.GeneralTransforming then
			if xushu:askForSkillInvoke(self, sgs.QVariant("transform::" .. player:objectName())) then
				room:broadcastSkillInvoke(self:objectName(), xushu)
				room:doAnimate(1, xushu:objectName(), player:objectName())
				return true
			end
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, xushu)
		if event == sgs.DamageInflicted then
			if xushu:canTransform() then
                room:transformDeputyGeneral(xushu)
			end
			local damage = data:toDamage()
			damage.damage = damage.damage - 1
			data:setValue(damage)
			if damage.damage < 1 then
				return true
			end
		end
		if event == sgs.GeneralTransforming then
			local count = data:toInt() + 2
			data:setValue(count)
		end
		return false
	end,
}

--diy_xushu:addSkill(zhuhai)
--diy_xushu:addSkill(pozhen)
--diy_xushu:addSkill(jiancai)

sgs.LoadTranslationTable{

	
    ["#diy_xushu"] = "Hoa Kiếm Vi Lê",
    ["diy_xushu"] = "Từ Thứ",
	["illustrator:diy_xushu"] = "Zero",
	["designer:diy_xushu"] = "Mộng Yểm & Lão Manh",
    ["zhuhai"] = "Tru Hại",
    [":zhuhai"] = "Khi bắt đầu giai đoạn kết thúc của người khác, nếu họ trong lượt này từng gây sát thương, bạn có thể sử dụng [Sát] không giới hạn tầm đánh với họ.",
    ["pozhen"] = "Phá Trận",
    [":pozhen"] = "Hạn định kỹ: Khi bắt đầu giai đoạn chuẩn bị của người khác, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Lệnh họ trong lượt chơi này không thể sử dụng/đánh ra/Trùng Chú bài trên tay;\n- Nếu họ trong quan hệ đội hình hoặc quan hệ vây công, bạn có thể bỏ 1 lá của những người khác có chung đội hình với họ hoặc người vây công trong quan hệ vây công với họ.",
    ["jiancai"] = "Tiến Tài",
    [":jiancai"] = "Phó tướng kỹ, Giảm 0.5 máu gốc:\n• Khi 1 người cùng thế lực với bạn nhận sát thương, nếu số sát thương không nhỏ hơn số máu của họ, bạn có thể lệnh sát thương này -1, sau đó bạn đổi tướng này.\n• Khi người cùng thế lực với bạn đổi phó tướng, bạn có thể lệnh số tướng để lựa chọn +2.",
    
    ["@zhuhai"] = "Có thể phát động »Tru Hại«, sử dụng [Sát] với %src",
    ["@pozhen-discard"] = "Phá Trận: Có thể bỏ 1 lá của người chung quan hệ đội hình hoặc vây công với %dest",
    ["jiancai:damage"] = "Có thể phát động »Tiến Tài«, -1 sát thương lên %src",
    ["jiancai:transform"] = "Có thể phát động »Tiến Tài«, số tướng được xem để lựa chọn +2",
	
	["cv:diy_xushu"] = "Nhất Mộc",
	["$zhuhai1"] = "Trượng kiếm hàng thiên hạ, trừ ác ngay bây giờ.",
	["$zhuhai2"] = "Quảng Nguyên, mau giết tên giặc này cho ta.",
	["$pozhen1"] = "Tử Long tướng quân đã vào cửa, trận này ắt bị phá.",
	["$pozhen2"] = "Trận mi tuy đẹp nhưng ta sẽ phá được.",
	["$jiancai1"] = "Nét chữ của mẹ già đang gọi, Thứ không thể không đi.",
	["$jiancai2"] = "Ngoạ Long là thiên tài vô song, sứ quân sao không đến cầu tài?",
	["~diy_xushu"] = "Mong mọi người làm việc tốt cho vua, đừng bắt đầu rồi kết thúc như ta.",


}

dizaiSummonCard = sgs.CreateArraySummonCard{
	name = "dizai",
    mute = true,
}

dizaiVS = sgs.CreateArraySummonSkill{
	name = "dizai",
	array_summon_card = dizaiSummonCard,
}

dizai = sgs.CreateTriggerSkill{
	name = "dizai",
	is_battle_array = true,
	battle_array_type = sgs.Siege,
	view_as_skill = dizaiVS,
	events = {sgs.DamageCaused},
	can_preshow = false,
    can_trigger = function(self, event, room, player, data)
		if room:alivePlayerCount() < 4 then return "" end
		local damage = data:toDamage()
		if player and player:isAlive() and damage.to and damage.to:isAlive() and player:isAdjacentTo(damage.to) then
			if damage.card and damage.card:isKindOf("Slash") and not (damage.chain or damage.transfer) then
				local skill_list = {}
				local name_list = {}
				
				local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skill_owner:hasShownSkill(self:objectName()) and player:inSiegeRelation(skill_owner, damage.to) then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
				return table.concat(skill_list,"|"), table.concat(name_list,"|")
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data, skill_owner)
		if skill_owner and skill_owner:hasShownSkill(self:objectName()) then 
			room:sendCompulsoryTriggerLog(skill_owner, self:objectName())
            room:broadcastSkillInvoke(self:objectName(), skill_owner)
			return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, skill_owner)
		local damage = data:toDamage()
		local ally = skill_owner
		local enemy = damage.to

		if ally == player then
			for _, p in sgs.qlist(room:getOtherPlayers(skill_owner)) do
				if p:inSiegeRelation(skill_owner, enemy) then
					ally = p
					break
				end
			end
		end

		room:doBattleArrayAnimate(skill_owner, enemy)

		if room:askForDiscard(ally, "dizai_invoke", 1, 1, true, true, "@dizai_discard:" .. player:objectName() .. ":" .. enemy:objectName()) then
			damage.damage = damage.damage + 1
			data:setValue(damage)
		end
		return false
	end,
}


--chendao:addSkill("wanglie")
--chendao:addSkill(dizai)


sgs.LoadTranslationTable{
	["#diy_chendao"] = "Bạch Nhị Đốc",
	["diy_chendao"] = "Trần Đáo",
	["designer:diy_chendao"] = "Mộng Yểm Cuồng Triều",
	["illustrator:diy_chendao"] = "Bành Hiểu Kiện",
	
	["dizai"] = "Địa Tải",
	[":dizai"] = "Trận pháp kỹ: Quan hệ vây công: Nếu bạn là người vây công, khi 1 người vây công gây sát thương cho mục tiêu bị vây công của lá [Sát], người vây công khác bạn có thể bỏ 1 lá để lệnh sát thương này +1.",
	["@dizai_discard"] = "Địa Tải: Có thể bỏ 1 lá để lệnh sát thương %src gây cho %dest +1",

	["$dizai1"] = "Binh pháp rằng, đánh lâu bất lợi, chớ có tham công.",
	["$dizai2"] = "Sư đoàn tinh nhuệ, ai có thể chống lại?",
}

jutian = sgs.CreateTriggerSkill{
	name = "jutian",
	events = {sgs.Damage},
    can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) then
			local damage = data:toDamage()
			if damage.to and damage.to ~= player then
				if not player:hasFlag("jutian1Used") then
					return self:objectName()
				end
				if not player:hasFlag("jutian2Used") then
					for _, p in sgs.qlist(room:getAlivePlayers()) do
						if p:isFriendWith(damage.to) then
							return self:objectName()
						end
					end
				end
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data)
		local damage = data:toDamage()
		local targets = sgs.SPlayerList()
		for _, p in sgs.qlist(room:getAlivePlayers()) do
			if (not player:hasFlag("jutian1Used") and p:isFriendWith(player)) or
					(not player:hasFlag("jutian2Used") and damage.to and p:isFriendWith(damage.to)) then
				targets:append(p)
			end
		end
		if not targets:isEmpty() then
			local prompt = "@jutian"
			
			if not player:hasFlag("jutian1Used") then
				prompt = prompt .. "-fillhandcard"
			end
			if not player:hasFlag("jutian2Used") and damage.to then
				prompt = prompt .. "-discard::" .. damage.to:objectName()
			end
			
			local target = room:askForPlayerChosen(player, targets, self:objectName(), prompt, true, true)
		    if target then
				local d = sgs.QVariant()
		        d:setValue(target)
		        player:setTag("jutian_target", d)
				room:broadcastSkillInvoke(self:objectName(), player)
		        return true
			end
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
		local target = player:getTag("jutian_target"):toPlayer()
		player:removeTag("jutian_target")
		if target and target:isAlive() then
			local damage = data:toDamage()
			local choices = {}
			if not player:hasFlag("jutian1Used") and target:isFriendWith(player) then
				table.insert(choices, "fillhandcard")
			end
			if not player:hasFlag("jutian2Used") and damage.to and target:isFriendWith(damage.to) then
				table.insert(choices, "discard")
			end
			
			local d = sgs.QVariant()
			d:setValue(target)
			local choice = room:askForChoice(player, "jutian_choice", table.concat(choices,"+"), d, "@jutian-choice::".. target:objectName(), "fillhandcard+discard")
			if choice == "fillhandcard" then
				room:setPlayerFlag(player, "jutian1Used")
                target:fillHandCards(target:getMaxHp(), self:objectName())
			elseif choice == "discard" then
				room:setPlayerFlag(player, "jutian2Used")
				if target:getHandcardNum() > target:getHp() then
                    local x = math.min(target:getHandcardNum() - target:getHp(), 5)
                    room:askForDiscard(target, "jutian_discard", x, x)
                end
			end
		end
		return false
	end,
}

zhuhuan:addSkill(jutian)

sgs.LoadTranslationTable{

    ["#zhuhuan"] = "Khí Cao Hộ Tiền",
    ["zhuhuan"] = "Chu Hoàn",
	["illustrator:zhuhuan"] = "Huỳnh Quang Bút",
	["designer:zhuhuan"] = "Mộng Yểm Cuồng Triều",
    ["jutian"] = "Cự Thiên",
    [":jutian"] = "Một lần trong lượt của mỗi người đối với mỗi mục lựa chọn, sau khi bạn gây sát thương cho người khác, bạn có thể chọn 1 mục:\n1. Bạn chọn 1 người cùng thế lực với người đã nhận sát thương, lệnh họ bỏ bài trên tay đến khi bằng với số máu của họ, tối đa bỏ 5 lá;\n2. Bạn chọn 1 người cùng thế lực với bạn, lệnh họ bổ sung bài trên tay đến giới hạn máu của họ.",
    ["@jutian-fillhandcard-discard"] = "Có thể phát độ »Cự Thiên«, chọn 1 người cùng thế lực với bạn để bổ sung bài hoặc chọn 1 người cùng thế lực với %dest để bỏ bài",
    ["@jutian-fillhandcard"] = "Có thể phát độ »Cự Thiên«, chọn 1 người cùng thế lực với bạn để bổ sung bài",
    ["@jutian-discard"] = "Có thể phát độ »Cự Thiên«, chọn 1 người cùng thế lực với %dest để bỏ bài",
    
    ["@jutian-choice"] = "Cự Thiện: Chọn hiệu ứng để lệnh %dest thực hiện",
    ["jutian_choice:fillhandcard"] = "Bổ sung bài",
    ["jutian_choice:discard"] = "Bỏ bài",

	["$jutian2"] = "Cho đi khoản nhỏ, thu về khoản lớn!",
	["$jutian1"] = "Tên vô danh tiểu tốt nào dám tiến lên một bước?",
	["~zhuhuan"] = "Thành này cao sừng sững, ta chẳng thể công được...",
}

guojue = sgs.CreateTriggerSkill{
	name = "guojue",
	events = {sgs.Dying},
    can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) then
			local dying = data:toDying()
			if dying.who and dying.who:isAlive() and dying.damage and dying.damage.from == player and not dying.who:isNude() then
				return self:objectName() .. "->" .. dying.who:objectName()
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, skill_target, data, player)
		local d = sgs.QVariant()
		d:setValue(skill_target)
		if player:askForSkillInvoke(self:objectName(), d) then
			room:doAnimate(1, player:objectName(), skill_target:objectName())
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, skill_target, data, player)
		if player:canDiscard(skill_target, "he") then
            local card_id = room:askForCardChosen(player, skill_target, "he", self:objectName(), false, sgs.Card_MethodDiscard)
            room:throwCard(card_id, skill_target, player)
        end
		return false
	end,
}

guojuecompulsory = sgs.CreateTriggerSkill{
	name = "#guojue-compulsory",
	events = {sgs.GeneralShowed},
	frequency = sgs.Skill_Compulsory,
    can_trigger = function(self, event, room, player, data)
		if player:cheakSkillLocation("guojue", data) and player:getMark("guojueUsed") == 0 then
            return self:objectName()
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		room:sendCompulsoryTriggerLog(player, "guojue")
        room:broadcastSkillInvoke("guojue", player)
        room:addPlayerMark(player, "guojueUsed")
        return true
	end,
    on_effect = function(self, event, room, player, data)
		local target = room:askForPlayerChosen(player, room:getOtherPlayers(player), "guojue_damage", "@guojue-damage")
        room:damage(sgs.DamageStruct("guojue", player, target))
		return false
	end,
}

shangshiCard = sgs.CreateSkillCard{
	name = "shangshiCard",
	will_throw = false,
	handling_method = sgs.Card_MethodNone,
	about_to_use = function(self, room, cardUse)
		local source = cardUse.from
		local target = cardUse.to:first()
		local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_GIVE, source:objectName(), target:objectName(), "shangshi","")
		room:moveCardTo(self, target, sgs.Player_PlaceHand, reason)
	end
}

shangshigive = sgs.CreateViewAsSkill{
	name = "shangshigive",
	response_pattern = "@@shangshigive",
	view_filter = function(self, selected, to_select)
		return #selected < sgs.Self:getLostHp() and not to_select:isEquipped()
	end,
	view_as = function(self, cards)
		if #cards == sgs.Self:getLostHp() then
			local card = shangshiCard:clone()
			for var=1,#cards do card:addSubcard(cards[var]) end
			return card
		end
	end,
}

shangshi = sgs.CreateMasochismSkill{
	name = "shangshi",
	can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) and not player:isNude() then
			return self:objectName()
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data)
		if player:askForSkillInvoke(self:objectName()) then
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
	end,
	on_damaged = function(self, player, damage)
		local room = player:getRoom()
		local choice = room:askForChoice(player, self:objectName(), "discard+givecard")
		local invoke = false
        if choice == "discard" then
			invoke = room:askForDiscard(player, "shangshi_discard", 1, 1, true, true, "@shangshi-discard")
        elseif choice == "givecard" then
            invoke = (room:askForUseCard(player, "@@shangshigive", "@shangshi-give:::"..player:getLostHp()) ~= nil)
        end
		if invoke and player:isAlive() then
			local x = player:getLostHp()
			if x > 0 then
				player:drawCards(x, self:objectName())
			end
		end
	end,
}

zhangchunhua:addSkill(guojue)
zhangchunhua:addSkill(guojuecompulsory)
zhangchunhua:addSkill(shangshi)

xiliang:insertRelatedSkills("guojue", "#guojue-compulsory")

if not sgs.Sanguosha:getSkill("shangshigive") then skills:append(shangshigive) end


sgs.LoadTranslationTable{

	
    ["#zhangchunhua"] = "Lãnh Huyết Hoàng Hậu",
    ["zhangchunhua"] = "Trương Xuân Hoa",
	["illustrator:zhangchunhua"] = "Tuyết Quân S",
	["designer:zhangchunhua"] = "Tiểu Lang Phủ Tâm",
    ["guojue"] = "Quả Quyết",
    [":guojue"] = "• Sau khi bạn mở tướng này lần đầu tiên, bạn gây 1 sát thương cho 1 người khác.\n• Khi 1 người khác tiến vào trạng thái hấp hối do bạn gây sát thương, bạn có thể bỏ 1 lá của họ.",
    ["shangshi"] = "Thương Thệ",
    [":shangshi"] = "Sau khi bạn nhận sát thương, bạn có thể chọn bỏ 1 lá hoặc giao X lá trên tay bạn cho 1 người khác; nếu làm vậy, bạn rút X lá (X lá số máu bạn đã mất).",
    ["@guojue-damage"] = "Quả quyết: Chọn 1 người khác để gây 1 sát thương",
    ["@shangshi-card"] = "Có thể phát động »Thương Thệ«, chọn bỏ 1 lá hoặc giao %arg lá trên tay cho 1 người khác",
    ["@shangshi-card-full"] = "Có thể phát động »Thương Thệ«, chọn bỏ 1 lá",
	["shangshi:givecard"] = "Giao lá trên tay cho người khác",
	["shangshi:discard"] = "Bỏ 1 lá",
	["@shangshi-discard"] = "Thương Thệ: Chọn 1 lá để bỏ",
	["@shangshi-give"] = "Thương Thệ: Chọn %arg lá trên tay và giao cho người khác",


	["$shangshi1"] = "Vô tình làm thương người, cố tình làm thương thân",
	["$shangshi2"] = "Ta mất tám trăm, địch mất một nghìn!",
	["$guojue1"] = "Sống chết của ngươi liên quan gì đến ta?",
	["$guojue2"] = "Không đến không đi, không hận không oán.",
	["~zhangchunhua"] = "Sao ngươi dám làm vậy với ta....",
}

shefuCard = sgs.CreateSkillCard{
	name = "shefuCard",
	will_throw = false,
	target_fixed = true,
	mute = true,
	handling_method = sgs.Card_MethodNone,
	extra_cost = function(self, room, card_use)
		room:broadcastSkillInvoke("shefu", 1, card_use.from)
		card_use.from:addToPile("ambush", card_use.card:getSubcards(), false)
	end
}

shefuVS = sgs.CreateOneCardViewAsSkill{
	name = "shefu",
	filter_pattern = ".|.|.|hand",
	view_as = function(self, originalcard)
		local skillcard = shefuCard:clone()
		skillcard:addSubcard(originalcard)
		skillcard:setSkillName(self:objectName())
		skillcard:setShowSkill(self:objectName())
		return skillcard
	end,
	enabled_at_play = function(self, player)
		return not player:hasUsed("#shefuCard")
	end
}

shefu = sgs.CreateTriggerSkill{
	name = "shefu",
	events = {sgs.CardUsed, sgs.CardResponded, sgs.EventLoseSkill},
	view_as_skill = shefuVS,
	on_record = function(self, event, room, player, data)
		if event == sgs.EventLoseSkill and data:toString():split(":")[1] == self:objectName() and player then
			player:clearOnePrivatePile("ambush")
		end
	end,
    can_trigger = function(self, event, room, player, data)
		if event == sgs.CardUsed or event == sgs.CardResponded then
			local card = nil
			if event == sgs.CardUsed then
				local use = data:toCardUse()
				if use.m_isHandcard then
					card = use.card
				end
			else
				local response = data:toCardResponse()
				if response.m_isUse and response.m_isHandcard then
					card = response.m_card
				end
			end
			if card and card:getTypeId() ~= sgs.Card_TypeSkill then
				local skill_list = {}
				local name_list = {}
				local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skill_owner ~= player then
						for _, id in sgs.qlist(skill_owner:getPile("ambush")) do
							if card:sameCardNameWith(sgs.Sanguosha:getCard(id)) then
								table.insert(skill_list, self:objectName())
								table.insert(name_list, skill_owner:objectName())
								break
							end
						end
					end
				end
				return table.concat(skill_list,"|"), table.concat(name_list,"|")
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data, ask_who)
		local card = nil
		if event == sgs.CardUsed then
			card = data:toCardUse().card
		else
			card = data:toCardResponse().m_card
		end
		if card then
			local pattern = "%" .. card:objectName()
			if card:isKindOf("Slash") then
				pattern = "Slash"
			elseif card:isKindOf("Nullification") then
				pattern = "Nullification"
			end
			pattern = pattern .. "|.|.|ambush"

			local prompt = "@shefu-invoke:" .. player:objectName() .. "::" .. card:objectName()
			
			ask_who:setTag("ShefuUsedata", data)
			local ints = room:askForExchange(ask_who, self:objectName(), 1, 0, prompt, "ambush", pattern)
			ask_who:removeTag("ShefuUsedata")
			
			if not ints:isEmpty() then
				local log1 = sgs.LogMessage()
				log1.type = "#InvokeSkill"
				log1.from = ask_who
				log1.arg = self:objectName()
				room:sendLog(log1)
				room:notifySkillInvoked(ask_who, self:objectName())
				room:broadcastSkillInvoke(self:objectName(), 2, ask_who)
				local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_REMOVE_FROM_PILE, ask_who:objectName(), "shefu", "")
				local move = sgs.CardsMoveStruct(ints, nil, sgs.Player_DiscardPile, reason)
				room:moveCardsAtomic(move, false)
				return true
			end
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
		if event == sgs.CardUsed then
			local use = data:toCardUse()
			use.to:clear()
			local nullified_list = use.nullified_list
			table.insert(nullified_list, "_ALL_TARGETS")
			use.nullified_list = nullified_list
			data:setValue(use)
		elseif event == sgs.CardResponded then
			local response = data:toCardResponse()
			response.m_card:setTag("ResponseNegated", sgs.QVariant(true))
		end
		return false
	end,
}

shefucompulsory = sgs.CreatePhaseChangeSkill{
	name = "#shefu-compulsory",
	can_trigger = function(self, event, room, player)
		if skillTriggerable(player, "shefu") and player:getPhase() == sgs.Player_Start and player:getPile("ambush"):length() > 2 then
			return self:objectName()
		end
	end,
	on_cost = function(self, event, room, player)
		room:sendCompulsoryTriggerLog(player, "shefu")
		return true
	end,
	on_phasechange = function(self, player)
		local room = player:getRoom()
		local x = player:getPile("ambush"):length() - 2
		if x > 0 then
			local to_throw = room:askForExchange(player, "shefu_remove", x, x, "@shefu-remove:::" .. tostring(x), "ambush")
			if not to_throw:isEmpty() then
				local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_REMOVE_FROM_PILE, player:objectName(), "shefu", "")
				local move = sgs.CardsMoveStruct(to_throw, nil, sgs.Player_DiscardPile, reason)
				room:moveCardsAtomic(move, false)
			end
		end
		return false
	end,
}

benyu = sgs.CreateMasochismSkill{
	name = "benyu",
	can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) then
			local damage = data:toDamage()
			if damage.from and damage.from:isAlive() and damage.from:getHandcardNum() ~= player:getHandcardNum() then
				return self:objectName()
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data)
		local damage = data:toDamage()
		if damage.from and damage.from:isAlive() then
			if damage.from:getHandcardNum() > player:getHandcardNum() then
				local source_data = sgs.QVariant()
				source_data:setValue(damage.from)
				if player:askForSkillInvoke(self:objectName(), source_data) then
					room:broadcastSkillInvoke(self:objectName(), player)
					room:doAnimate(1, player:objectName(), damage.from:objectName())
					player:setTag("benyu_effect", sgs.QVariant("select"))
					return true
				end
			elseif damage.from:getHandcardNum() < player:getHandcardNum() then
				local x = damage.from:getHandcardNum() + 1
				local prompt = "@benyu-invoke::" .. damage.from:objectName() .. ":" .. tostring(x)
				player:setTag("BenyuDamagedata", data)
				local invoke = room:askForDiscard(player, "benyu", 998, x, true, false, prompt, true)
				player:removeTag("BenyuDamagedata")
				if invoke then
					room:broadcastSkillInvoke(self:objectName(), player)
                    room:doAnimate(1, player:objectName(), damage.from:objectName())
					player:setTag("benyu_effect", sgs.QVariant("damage"))
					return true
				end
			end
		end
		return false
	end,
	on_damaged = function(self, player, damage)
		local room = player:getRoom()
		local effect_name = player:getTag("benyu_effect"):toString()
		player:removeTag("benyu_effect")
		if effect_name == "damage" then
			room:damage(sgs.DamageStruct(self:objectName(), player, damage.from, 1))
		elseif effect_name == "select" and player:isAlive() then
			local source_data = sgs.QVariant()
			source_data:setValue(damage.from)
			local choice = room:askForChoice(player, self:objectName(), "draw+discard", source_data, "@benyu-choose::" .. damage.from:objectName())
            if choice == "draw" then
                player:fillHandCards(math.min(damage.from:getHandcardNum(),5) , self:objectName())
            elseif choice == "discard" then
                local x = math.min(damage.from:getHandcardNum()-player:getHandcardNum(), 5)
                room:askForDiscard(damage.from, "benyu_discard", x, x)
            end
		end
	end,
}

chengyu:addSkill(shefu)
chengyu:addSkill(shefucompulsory)
chengyu:addSkill(benyu)

xiliang:insertRelatedSkills("shefu", "#shefu-compulsory")

sgs.LoadTranslationTable{
	
    ["#chengyu"] = "Thái Sơn Phụng Nhật",
    ["chengyu"] = "Trình Dục",
	["illustrator:chengyu"] = "Mr_Sleeping",
	["designer:chengyu"] = "Mộng Yểm Cuồng Triều",
    ["shefu"] = "Phục Binh",
    [":shefu"] = "• Một lần trong giai đoạn ra bài, bạn có thể đặt 1 lá trên tay lên tướng của bạn, gọi là [Phục Binh].\n• Khi 1 người khác sử dụng bài trên tay, bạn có thể đưa 1 [Phục Binh] có cùng tên với lá đó vào chồng bài bỏ, hủy bỏ hoàn toàn lá đó.\n• Khi bắt đầu giai đoạn chuẩn bị, nếu số [Phục Binh] > 2, bạn đưa số [Phục Binh] vào chồng bài bỏ đến khi còn 2.",
    ["benyu"] = "Bí Dục",
    [":benyu"] = "Sau khi bạn nhận sát thương, nếu bài trên tay bạn so với nguồn sát thương:\n* Ít hơn: Bạn có thể chọn 1 mục:\n 1. Bổ sung bài trên tay đến khi bằng với họ, tối đa 5 lá;\n 2. Lệnh họ bỏ đi bài trên tay đến khi bằng bạn, tối đa bỏ 5 lá.\n* Nhiều hơn: Bạn có thể bỏ số bài trên tay bằng số bài trên tay họ +1, sau đó gây 1 sát thương cho họ.",

    ["ambush"] = "Phục Binh",
    ["@shefu-invoke"] = "Có thể phát động »Phục Binh«, bỏ 1 [Phục Binh] có tên [%arg] để hủy bỏ hoàn toàn lá [%arg] do %src sử dụng",
    ["@shefu-remove"] = "Phục Binh: chọn 1 [Phục Binh] để bỏ",
    ["#shefu-compulsory"] = "Phục Binh",

	["@benyu-invoke"] = "Có thể phát động »Bí Dục«, bỏ %arg lá trên tay để gây 1 sát thương cho %dest",
    ["@benyu-choose"] = "Bí Dục: Chọn phương pháp để bài trên tay bạn bằng với %dest",
    ["benyu:draw"] = "Bạn bổ sung bài",
    ["benyu:discard"] = "Họ bỏ bài",

	["$shefu1"] = "Bẫy đã đặt, mai phục đã xong, chỉ chờ quân địch xông vào!",
	["$shefu2"] = "Bầu trời dày đặc như này, dù người có lắp thêm cách cũng khó bề thoát thân!",
	["$benyu2"] = "Thiên hạ đại loạn, lúc này quần hùng mà khơi binh, thế nào cũng gây được tiếng tăm!",
	["$benyu1"] = "Trí lược của Tào Công đúng là món quà trời ban!",
	["~chengyu"] = "Chính lúc nước nhà cần người báo đáp, ta lại không còn nữa!",
}

jingce = sgs.CreateTriggerSkill{
	name = "jingce",
	events = {sgs.CardUsed, sgs.CardResponded, sgs.EventPhaseChanging, sgs.CardFinished},
	on_record = function(self, event, room, player, data)
		if (event == sgs.CardUsed or event == sgs.CardResponded) and player:getPhase() == sgs.Player_Play then
			local card = nil
			if event == sgs.CardUsed then
				local use = data:toCardUse()
				card = use.card
			else
				local response = data:toCardResponse()
				if response.m_isUse then
					card = response.m_card
				end
			end
			if card and card:getTypeId() ~= sgs.Card_TypeSkill then
				room:addPlayerMark(player, "jingce_record")
				local x = player:getMark("jingce_record")
				if player:hasShownSkill(self:objectName()) then
					room:setPlayerMark(player, "#jingce", x)
				end
				card:setTag("JingceRecord", sgs.QVariant(x))
			end
		elseif event == sgs.EventPhaseChanging then
			local change = data:toPhaseChange()
		    if change.from == sgs.Player_Play or change.to == sgs.Player_Play then
				room:setPlayerMark(player, "jingce_record", 0)
				room:setPlayerMark(player, "#jingce", 0)
			end
		end
	end,
    can_trigger = function(self, event, room, player, data)
		if event == sgs.CardFinished and skillTriggerable(player, self:objectName()) and player:getPhase() == sgs.Player_Play and player:hasShownOneGeneral() then
			local use = data:toCardUse()
			if use.card and use.card:getTypeId() ~= sgs.Card_TypeSkill and not use.card:isKindOf("ThreatenEmperor") then
				local x = use.card:getTag("JingceRecord"):toInt()
				if x == player:getHp() then
					local all_players = room:getAlivePlayers()
					local can_invoke = false
					for _, p in sgs.qlist(all_players) do
						if p:getHp() < 1 then
							return ""
						end
						if not player:isFriendWith(p) and p:hasShownOneGeneral() then
							can_invoke = true
						end
					end
					if can_invoke then
						return self:objectName()
					end
				end
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data)
		local targets = sgs.SPlayerList()
		for _, p in sgs.qlist(room:getAlivePlayers()) do
			if not player:isFriendWith(p) and p:hasShownOneGeneral() then
				targets:append(p)
			end
		end
		if not targets:isEmpty() then
			local target = room:askForPlayerChosen(player, targets, self:objectName(), "jingce-invoke", true, true)
		    if target then
				local d = sgs.QVariant()
		        d:setValue(target)
		        player:setTag("jingce_target", d)
				room:broadcastSkillInvoke(self:objectName(), player)
		        return true
			end
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
		local target = player:getTag("jingce_target"):toPlayer()
		player:removeTag("jingce_target")
		if target and target:isAlive() and player:isAlive() and not player:askCommandto(self:objectName(), target) then
            player:drawCards(2, self:objectName())
		end
		return false
	end,
}

guohuai:addSkill(jingce)

sgs.LoadTranslationTable{

	["#guohuai"] = "Thùy Vấn Tần Ung",
    ["guohuai"] = "Quách Hoài",
	["designer:guohuai"] = "Mộng Yểm Cuồng Triều",
	["illustrator:guohuai"] = "DH",
    ["jingce"] = "Tinh Sách",
    [":jingce"] = "Giai đoạn ra bài, sau khi lá thứ X do bạn sử dụng kết toán xong (X là số máu hiện tại của bạn), nếu không có ai đang giải quyết hấp hối, bạn có thể yêu cầu 1 người thế lực xác định khác bạn chấp hành 1 [Quân Lệnh], nếu họ không chấp hành, bạn rút 2 lá.",
    ["jingce-invoke"] = "Có thể phát động »Tinh Sách«, chọn 1 người khác thế lực chấp hành quân lệnh.",

	["$jingce1"] = "Sách lược tinh tường, không lo bị loạn.",
	["$jingce2"] = "Tinh binh cự địch, sách thủ như sơn.",
	["~guohuai"] = "Khương Duy tiểu nhân, không ngờ...",
}


mumeng = sgs.CreateOneCardViewAsSkill{
	name = "mumeng",
	filter_pattern = ".|heart|.|hand",
	view_as = function(self, to_select)
		local card_name = sgs.Self:getTag("mumeng"):toString()
		if card_name ~= "" then
			local card = sgs.Sanguosha:cloneCard(card_name)
			card:setCanRecast(false)
			card:addSubcard(to_select:getId())
			card:setSkillName("mumeng")
			card:setShowSkill("mumeng")
			return card
		end
	end,
    enabled_at_play = function(self, player)
		return player:usedTimes("ViewAsSkill_mumengCard") < 1
	end,
	vs_card_names = function(self, selected)
		if #selected == 1 then
			return "befriend_attacking+fight_together"
		end
		return ""
	end,
}

naman = sgs.CreateTriggerSkill{
	name = "naman",
	events = {sgs.TargetChoosing},
    can_trigger = function(self, event, room, player, data)
		if event == sgs.TargetChoosing and player and player:isAlive() then
			local use = data:toCardUse()
			if use.card and use.card:getTypeId() ~= sgs.Card_TypeSkill and use.card:isBlack() and room:getUseAliveTargets(use):length() > 1 then
				local skill_list = {}
				local name_list = {}
				local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skillTriggerable(skill_owner, self:objectName()) and player ~= skill_owner then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
				return table.concat(skill_list,"|"), table.concat(name_list,"|")
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data, skill_owner)
		if skill_owner:askForSkillInvoke(self:objectName(), data) then
			room:broadcastSkillInvoke(self:objectName(), skill_owner)
			return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, skill_owner)
		local judge = sgs.JudgeStruct()
		judge.pattern = ".|spade"
		judge.good = false
		judge.who = skill_owner
		judge.reason = self:objectName()
		room:judge(judge)
		if judge:isGood() and skill_owner:isAlive() then
			local use = data:toCardUse()
			local targets = room:getUseExtraTargets(use, false)
			for _, p in sgs.qlist(use.to) do
				if p:isAlive() then
					targets:append(p)
				end
			end
			if not targets:isEmpty() then
				local prompt = "@naman-target:" .. player:objectName() .. "::" .. use.card:objectName()
				skill_owner:setTag("NamanUsedata", data)
				local target = room:askForPlayerChosen(skill_owner, targets, "naman_target", prompt)
				skill_owner:removeTag("NamanUsedata")
				room:doAnimate(1, skill_owner:objectName(), target:objectName())
				if use.to:contains(target) then
					sgs.Room_cancelTarget(use, target)
				else
					use.to:append(target)
					if (use.card:hasFlag("BladeEffect")) then
						room:setPlayerDisableShow(target, "hd", "Blade");
					end
					room:sortByActionOrder(use.to)
				end
				data:setValue(use)
			end
		end
		return false
	end,
}

maliang:addSkill(mumeng)
maliang:addSkill(naman)

sgs.LoadTranslationTable{

    ["#maliang"] = "Bạch Mi Lệnh Sĩ",
    ["maliang"] = "Mã Lương",
	["designer:maliang"] = "Mộng Yểm Cuồng Triều",
	["illustrator:maliang"] = "biou09",
    ["mumeng"] = "Mục Minh",
    [":mumeng"] = "Một lần trong giai đoạn ra bài, bạn có thể chuyển hóa sử dụng 1 lá CƠ trên tay thành [Viễn Giao Cận Công]/[Lục Lực Đồng Tâm]",
    ["naman"] = "Nạp Man",
    [":naman"] = "Khi người khác sử dụng bài Đen có chỉ định nhiều mục tiêu, bạn có thể tiến hành phán xét, nếu kết quả phát xét không phải BÍCH, bạn chọn 1 mục:\n1. Lệnh 1 người khác trở thành mục tiêu của bài (Không bị giới hạn khoảng cách);\n2. Hủy bỏ 1 mục tiêu của lá đó.",
	--["@mumeng-choose"] = "Mục Minh: Chọn lá muốn sử dụng",
	--["@mumeng-usecard"] = "Mục Minh: Chọn lá CƠ để chuyển hóa sử dụng thành [%arg]",
    ["@naman-target"] = "Nạp Man: Thêm hoặc bớt 1 mục tiêu của [%arg] do %src sử dụng",
	
	["$mumeng1"] = "Tính tình ngang ngược, đau người hại ta.",
	["$mumeng2"] = "Nghỉ ngơi để tiếp tục chiến sự",
	["$naman2"] = "Chờ đã, ta đến đây!",
	["$naman1"] = "Bỏ tối theo sáng, chiếu rọi vào bậu cửa.",
	["~maliang"] = "Hoàng thúc sao không nghe lời ta...",
}

dingke = sgs.CreateTriggerSkill{
	name = "dingke",
	events = {sgs.CardsMoveOneTime},
    can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) and not player:hasFlag("DingkeUsed") then
			local current = room:getCurrent()
			if current and current:isAlive() and current:getPhase() ~= sgs.Player_NotActive then
				local move_datas = data:toList()
				for _, move_data in sgs.qlist(move_datas) do
					local move = move_data:toMoveOneTime()
					local reasonx = bit32.band(move.reason.m_reason, sgs.CardMoveReason_S_MASK_BASIC_REASON)
					if reasonx ~= sgs.CardMoveReason_S_REASON_USE and reasonx ~= sgs.CardMoveReason_S_REASON_RESPONSE then
						if move.from_places:contains(sgs.Player_PlaceHand) or move.from_places:contains(sgs.Player_PlaceEquip) then
							if move.from and move.from:isAlive() and move.from:getPhase() == sgs.Player_NotActive and player:isFriendWith(move.from) then
								if not current:isKongcheng() or (move.from:objectName() ~= player:objectName() and not player:isKongcheng()) then
									return self:objectName()
								end
							end
						end
					end
				end
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		local current = room:getCurrent()
		if current and current:isAlive() and current:getPhase() ~= sgs.Player_NotActive then
			local targets = sgs.SPlayerList()
			if not current:isKongcheng() then
				targets:append(current)
			end
			local move_datas = data:toList()
			for _, move_data in sgs.qlist(move_datas) do
				local move = move_data:toMoveOneTime()
				local reasonx = bit32.band(move.reason.m_reason, sgs.CardMoveReason_S_MASK_BASIC_REASON)
				if reasonx ~= sgs.CardMoveReason_S_REASON_USE and reasonx ~= sgs.CardMoveReason_S_REASON_RESPONSE then
					if move.from_places:contains(sgs.Player_PlaceHand) or move.from_places:contains(sgs.Player_PlaceEquip) then
						if move.from and move.from:isAlive() and move.from:getPhase() == sgs.Player_NotActive and player:isFriendWith(move.from) then
							if move.from:objectName() ~= player:objectName() and not player:isKongcheng() then
								local move_from = getServerPlayer(room, move.from:objectName())
								if move_from then
									targets:append(move_from)
								end
							end
						end
					end
				end
			end
			if not targets:isEmpty() then
				local target = room:askForPlayerChosen(player, targets, self:objectName(), "dingke-invoke::" .. current:objectName(), true, true)
				if target then
					local d = sgs.QVariant()
					d:setValue(target)
					player:setTag("dingke_target", d)
					player:setFlags("DingkeUsed")
					room:broadcastSkillInvoke(self:objectName(), player)
					return true
				end
			end
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
		local target = player:getTag("dingke_target"):toPlayer()
		player:removeTag("dingke_targetdingke_target")
		if target and target:isAlive() then
            if target:getPhase() ~= sgs.Player_NotActive then
				room:askForDiscard(target, "dingke_discard", 1, 1)
                if player:isAlive() and player:getMark("@halfmaxhp") < player:getMaxHp() then
                    room:addPlayerMark(player, "@halfmaxhp")
				end
			elseif player:isAlive() and not player:isKongcheng() then
				target:setFlags("DingkeTarget")
                local result = room:askForExchange(player, "dingke_give", 1, 1, "@dingke-give::" .. target:objectName(), "", ".|.|.|hand")
                target:setFlags("-DingkeTarget")
				if not result:isEmpty() then
					local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_GIVE, player:objectName(), target:objectName(), self:objectName(), "")
					local move = sgs.CardsMoveStruct(result, target, sgs.Player_PlaceHand, reason)
					room:moveCardsAtomic(move, false)
					if player:isAlive() and player:getMark("@halfmaxhp") < player:getMaxHp() then
						room:addPlayerMark(player, "@halfmaxhp")
					end
				end
			end
		end
		return false
	end,
}

jiyuan = sgs.CreateTriggerSkill{
	name = "jiyuan",
	events = {sgs.CardsMoveOneTime, sgs.Dying},
    can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) then
			if event == sgs.CardsMoveOneTime then
				local move_datas = data:toList()
				for _, move_data in sgs.qlist(move_datas) do
					local move = move_data:toMoveOneTime()
					if move.reason.m_skillName == "dingke" and move.from:objectName() == player:objectName() and move.to and move.to:isAlive() then
						return self:objectName() .. ":" .. move.to:objectName()
					end
				end
			elseif event == sgs.Dying then
				local dying = data:toDying()
				if dying.who and dying.who:isAlive() then
					return self:objectName() .. ":" .. dying.who:objectName()
				end
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, skill_target, data, player)
		local d = sgs.QVariant()
		d:setValue(skill_target)
		if player:askForSkillInvoke(self:objectName(), d) then
			room:doAnimate(1, player:objectName(), skill_target:objectName())
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, skill_target, data, player)
		skill_target:drawCards(1, self:objectName())
		return false
	end,
}

yijibo:addSkill(dingke)
yijibo:addSkill(jiyuan)

sgs.LoadTranslationTable{

    ["#yijibo"] = "Kiến Lễ Vu Thế",
    ["yijibo"] = "Y Tịch",
	["illustrator:yijibo"] = "DH",
	["designer:yijibo"] = "Mộng Yểm Cuồng Triều",
    ["dingke"] = "Định Khoa",
    [":dingke"] = "Một lần trong lượt của mỗi người, sau khi 1 người cùng thế lực với bạn mất bài ngoài lượt không vì sử dụng/đánh ra, bạn có thể chọn 1 mục:\n1. Giao 1 lá trên tay cho họ;\n2. Lệnh người đang có lượt bỏ 1 lá trên tay;\n▷ Nếu số [Âm dương ngư] của bạn < giới hạn máu, bạn thu lấy 1 tiêu ký [Âm dương ngư].",
    ["jiyuan"] = "Cấp Viện",
    [":jiyuan"] = "Khi có người tiến vào trạng thái hấp hối hoặc sau khi có người được bạn giao bài do phát động »Định Khoa«, bạn có thể lệnh họ rút 1 lá.",

	["dingke-invoke"] = "Có thể phát động »Định Khoa«, chọn %dest để lệnh họ bỏ 1 lá trên tay hoặc chọn người vừa mất bài để giao họ 1 lá trên tay",
    ["@dingke-give"] = "Định Khoa: Chọn 1 lá trên tay và giao cho %dest",
	
	["$dingke1"] = "Bái lạy một cái, có gì cực khổ đâu",
	["$dingke2"] = "Để ý từng cử chỉ lời nói, thì mới có thể ung dung phong nghị",
	["$jiyuan1"] = "Nếu chủ công không tránh, sẽ bị Thái Mạo hãm hại đấy!",
	["$jiyuan2"] = "Tình hình nguy cấp, xin hãy đi mau!",
	["~yijibo"] = "Còn chưa kịp...giúp Lưu công trốn thoát.....",
}

kangrui = sgs.CreateTriggerSkill{
	name = "kangrui",
	events = {sgs.EventPhaseChanging, sgs.ConfirmDamage, sgs.TargetChoosing},
	on_record = function(self, event, room, player, data)
		if event == sgs.ConfirmDamage then
			local damage = data:toDamage()
			if damage.card and damage.card:getSkillName() == self:objectName() then
				damage.damage = damage.damage + 1
				data:setValue(damage)
			end
		elseif event == sgs.EventPhaseChanging then
			local all_players = room:getAlivePlayers()
			for _, p in sgs.qlist(all_players) do
				room:setPlayerMark(p, "##kangrui", 0)
				p:setFlags("-kangruiUsed")
			end
		end
	end,
    can_trigger = function(self, event, room, player, data)
		if event == sgs.TargetChoosing and player and player:isAlive() and player:getPhase() == sgs.Player_Play then
			local use = data:toCardUse()
			if use.card and use.card:getTypeId() ~= sgs.Card_TypeSkill and use.to:length() == 1 and not use.to:contains(player) then
				local skill_list = {}
				local name_list = {}
				local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skillTriggerable(skill_owner, self:objectName()) and player:isFriendWith(skill_owner) and not skill_owner:hasFlag("kangruiUsed") then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
				return table.concat(skill_list,"|"), table.concat(name_list,"|")
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player, data, skill_owner)
		local use = data:toCardUse()
        if use.to:length() ~= 1 then return false end
        local target = use.to:first()
        local prompt = "prompt:" .. player:objectName() .. ":" .. target:objectName() .. ":" .. use.card:objectName()
		
		player:setTag("KangruiUsedata", data)
		local invoke = skill_owner:askForSkillInvoke(self, sgs.QVariant(prompt))
		player:removeTag("KangruiUsedata")
		if invoke then
			room:broadcastSkillInvoke(self:objectName(), skill_owner)
            skill_owner:setFlags("kangruiUsed")
			return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, skill_owner)
		local use = data:toCardUse()
        if use.to:length() ~= 1 then return false end
        local target = use.to:first()
		sgs.Room_cancelTarget(use, target)
		data:setValue(use)
		local choices = {"fillhandcards"}
		local duel = sgs.Sanguosha:cloneCard("duel", sgs.Card_NoSuit, 0)
		duel:setSkillName("_kangrui")
		if not target:isCardLimited(duel, sgs.Card_MethodUse) and not target:isProhibited(player, duel) then
			local all_safe = true
			for _, p in sgs.qlist(room:getAlivePlayers()) do
				if p:getHp() < 1 then
					all_safe = false
					break
				end
			end
			if all_safe then
				table.insert(choices, "useduel")
			end
		end
		local d = sgs.QVariant()
		d:setValue(target)
		local choice = room:askForChoice(player, self:objectName(), table.concat(choices, "+"), d, "@kangrui-choose::" .. target:objectName(), "fillhandcards+useduel")
		if choice == "fillhandcards" then
			player:fillHandCards(player:getHp(), self:objectName())
            room:addPlayerMark(player, "##kangrui")
		elseif choice == "useduel" then
			room:useCard(sgs.CardUseStruct(duel, target, player), false)
		end
		return false
	end,
}

kangruiprohibit = sgs.CreateProhibitSkill{
	name = "#kangrui-prohibit" ,
	is_prohibited = function(self, from, to, card)
		if from and from:getMark("##kangrui") > 0 and card:getTypeId() ~= sgs.Card_TypeSkill then
			return (to and from ~= to)
		end
		return false
	end
}

zhangyi:addSkill(kangrui)
zhangyi:addSkill(kangruiprohibit)

xiliang:insertRelatedSkills("kangrui", "#kangrui-prohibit")

sgs.LoadTranslationTable{

    ["#zhangyi"] = "Tranh Hổ",
    ["zhangyi"] = "Trương Dực",
	["illustrator:zhangyi"] = "Ảnh Tử C",
	["designer:zhangyi"] = "Mộng Yểm Cuồng Triều",
    ["kangrui"] = "Kháng Nhuệ",
    [":kangrui"] = "Một lần trong giai đoạn ra bài của 1 người cùng thế lực với bạn, khi họ sử dụng bài có chỉ định 1 người khác làm mục tiêu duy nhất, bạn có thể hủy bỏ mục tiêu của lá đó, lệnh họ chọn 1 mục:\n1. Bổ sung bài trên tay đến X lá (X là số máu của họ), giai đoạn này, họ không thể chỉ định người ngoài họ làm mục tiêu của bài;\n2. Nếu không có người trong trạng thái hấp hối, lệnh mục tiêu ban đầu của lá đó xem như sử dụng [Quyết đấu] với họ, số sát thương của [Quyết đấu] này +1.",
    
    ["kangrui:prompt"] = "Có thể phát động »Kháng Nhuệ«, hủy bỏ mục tiêu %dest từ lá [%arg] của %src",
    ["@kangrui-choose"] = "Kháng Nhuệ: Chọn bổ sung bài trên tay đến giới hạn máu hoặc lệnh %dest xem như sử dụng [Quyết Đấu] với bạn",
    ["kangrui:fillhandcards"] = "Bổ sung bài",
    ["kangrui:useduel"] = "Quyết Đấu",

	["$kangrui1"] = "尔等魍魉，愿试吾剑之利乎？",
	["$kangrui2"] = "诸军鼓励，克复中原，指日可待！",
	["~zhangyi"] = "伯约不见，疲惫之国力乎……",
}



lifuCard = sgs.CreateSkillCard{
	name = "lifuCard",
	filter = function(self, targets, to_select)
		return #targets == 0
	end,
    on_effect = function(self, effect)
		local source = effect.from
		local target = effect.to
		local room = source:getRoom()
		room:askForDiscard(target, "lifu_discard", 2, 2, false, true)
		
		if source:isAlive() and target:isAlive() then
			local ids = room:getNCards(1)
			local card = sgs.Sanguosha:getCard(ids:first())
			room:fillAG(ids, source)
			room:askForSkillInvoke(source, "lifu_view", sgs.QVariant("prompt::" .. target:objectName() .. ":" .. card:objectName()), false)
			room:clearAG(source)

			source:setFlags("Global_GongxinOperator")
			local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_PREVIEWGIVE, source:objectName(), target:objectName(), "lifu", "")
			room:moveCardTo(card, target, sgs.Player_PlaceHand, reason)
			source:setFlags("-Global_GongxinOperator")
			
		end
	end,
}

lifu = sgs.CreateZeroCardViewAsSkill{   
	name = "lifu",
	view_as = function(self)
		local skillcard = lifuCard:clone()
		skillcard:setSkillName(self:objectName())
		skillcard:setShowSkill(self:objectName())
		return skillcard
	end,
	enabled_at_play = function(self, player)
		return not player:hasUsed("#lifuCard")
	end,
}

yanzhong = sgs.CreatePhaseChangeSkill{
	name = "yanzhong",
	can_trigger = function(self, event, room, player)
		if skillTriggerable(player, self:objectName()) and player:getPhase() == sgs.Player_Finish then
			for _, p in sgs.qlist(room:getOtherPlayers(player)) do
				if not player:isKongcheng() then
					return self:objectName()
				end
			end
		end
		return ""
	end,
	on_cost = function(self, event, room, player)
		local targets = sgs.SPlayerList()
		for _, p in sgs.qlist(room:getOtherPlayers(player)) do
			if not player:isKongcheng() then
				targets:append(p)
			end
		end
		if not targets:isEmpty() then
			local target = room:askForPlayerChosen(player, targets, self:objectName(), "@yanzhong", true, true)
		    if target then
				local d = sgs.QVariant()
		        d:setValue(target)
		        player:setTag("yanzhong_target", d)
				room:broadcastSkillInvoke(self:objectName(), player)
		        return true
			end
		end
		return false
	end,
	on_phasechange = function(self, player)
		local room = player:getRoom()
		local target = player:getTag("yanzhong_target"):toPlayer()
		player:removeTag("yanzhong_target")
		
		if player:isAlive() and target and target:isAlive() and player:canDiscard(target, "h") then
			local suit = room:askForSuit(player, self:objectName())
			
			local log = sgs.LogMessage()
			log.type = "#ChooseSuit"
			log.from = player
			log.arg = sgs.Card_Suit2String(suit)
			room:sendLog(log)
			
			local to_throw = room:askForCardChosen(player, target, "h", self:objectName(), false, sgs.Card_MethodDiscard)

			local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_DISMANTLE, player:objectName(), target:objectName(), self:objectName(), "")
			
			local dis_move = sgs.CardsMoveStruct(to_throw, nil, sgs.Player_DiscardPile, reason)
			
			local data = room:moveCardsSub(dis_move, true)
			
			local same_suit = false
			local not_same_suit = false
			
			local move_datas = data:toList()
			for _, move_data in sgs.qlist(move_datas) do
				local move = move_data:toMoveOneTime()
				if move.from:objectName() == target:objectName() and move.reason.m_reason == sgs.CardMoveReason_S_REASON_DISMANTLE then
					local i = 0
					for _, card_str in pairs(move.cards)do
						local card = sgs.Card_Parse(card_str)
						if card and (move.from_places:at(i) == sgs.Player_PlaceHand or move.from_places:at(i) == sgs.Player_PlaceEquip) then
							if card:getSuit() == suit then
								same_suit = true
							else
								not_same_suit = true
							end
						end
						i = i + 1
					end
				end
			end
			
			if same_suit then
				if suit == sgs.Card_Heart then
					room:recover(player, sgs.RecoverStruct())
				end
				if suit == sgs.Card_Diamond then
					player:drawCards(1, self:objectName())
					if player:isChained() then
						room:setPlayerProperty(player, "chained", sgs.QVariant(false))
					end
				end
				if suit == sgs.Card_Spade then
					room:loseHp(target)
				end
				if suit == sgs.Card_Club and player:isAlive() and target:isAlive() and not target:isNude() then
					local cards = room:askForExchange(target, "yuancong_give", 1, 1, "@yanzhong-give:" .. player:objectName())
					if not cards:isEmpty() then
						local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_GIVE, target:objectName(), player:objectName(), self:objectName(), "")
						local move = sgs.CardsMoveStruct(cards, player, sgs.Player_PlaceHand, reason)
						room:moveCardsAtomic(move, false)
					end
				end
			end
			if not_same_suit then
				room:askForDiscard(player, "yanzhong_discard", 1, 1, false, true)
			end
		end
		
	end,
}

guyong:addSkill(lifu)
guyong:addSkill(yanzhong)

sgs.LoadTranslationTable{

	["#guyong"] = "Miếu Đường Đích Ngọc Khách",
	["guyong"] = "Cố Ung",
	["designer:guyong"] = "Cẩm Phàm Du Hiệp_Cam",
	["illustrator:guyong"] = "sky",
	["lifu"] = "Lễ Phụ",
	[":lifu"] = "Một lần trong giai đoạn ra bài, bạn có thể chọn 1 người, lệnh họ bỏ 2 lá, sau đó bạn xem lá trên đầu chồng bài rút và giao cho họ.",
	["yanzhong"] = "Ngôn Trung",
	[":yanzhong"] = "Khi bắt đầu giai đoạn kết thúc, bạn có thể chọn 1 chất và chọn 1 người khác có bài trên tay, bạn bỏ 1 lá trên tay họ; nếu chất của lá đã bỏ và chất đã đoán:\n* Khác chất: bạn bỏ 1 lá;\n* Cùng chất và chất đó là:\nCƠ: Bạn hồi 1 máu;\nRÔ: Bạn rút 1 lá, loại bỏ trạng thái xích;\nTÉP: Họ giao 1 lá cho bạn;\nBÍCH: Họ mất 1 máu.",
	["lifu_view:prompt"] = "Lễ Phụ: Lá [%arg] này sẽ được giao cho %dest",
	["@yanzhong"] = "Có thể phát động »Ngôn Trung«, chọn 1 người khác có bài trên tay",
	["@yanzhong-give"] = "Ngôn Trung: Chọn 1 lá và giao cho %src",

	["$lifu2"] = "Phải biết thẩm thời đạc thế, thì mới lường được mọi đổi thay",
	["$lifu1"]= "Chuyện này cần cân nhắc lại",
	["$yanzhong1"] = "Luôn giữ vững sự công chính vô tư",
	["$yanzhong2"] = "Chư quân hãy nhìn kỹ vào",
	["~guyong"] = "Bênh tật ngày một nghiêm trọng, xem ra quốc sự khó bề yên ổn...",

}

huxun = sgs.CreateTriggerSkill{
	name = "huxun",
	events = {sgs.EventPhaseChanging, sgs.Dying},
	on_record = function(self, event, room, player, data)
		if event == sgs.Dying then
			local dying = data:toDying()
			if dying.who ~= player and dying.damage and dying.damage.from == player then
				room:setPlayerFlag(player, "GlobalDyingCaused")
			end
		end
	end,
    can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		if event == sgs.EventPhaseChanging then
		    local change = data:toPhaseChange()
		    if change.to == sgs.Player_NotActive then
			    local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skillTriggerable(skill_owner, self:objectName()) and skill_owner:hasFlag("GlobalDyingCaused") then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
		    end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
    on_cost = function(self, event, room, current, data, player)
		if player:askForSkillInvoke(self:objectName()) then
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, current, data, player)
		local choices = {"movecard"}
		
		local can_recover = false
		for _,p in sgs.qlist(room:getOtherPlayers(player)) do
			if p:getMaxHp() >= player:getMaxHp() then
				can_recover = true
				break
			end
		end
		if can_recover then
			table.insert(choices, "gainmaxhp")
		end

        local choice = room:askForChoice(player, self:objectName(), table.concat(choices,"+"), data, "", "gainmaxhp+movecard")
		if choice == "gainmaxhp" then
			local log = sgs.LogMessage()
			log.type = "#GainMaxHp"
			log.from = player
			log.arg = "1"
			room:sendLog(log)
			room:setPlayerProperty(player, "maxhp", sgs.QVariant(player:getMaxHp() + 1))
			local recover = sgs.RecoverStruct()
			recover.who = player
			room:recover(player, recover)
		elseif choice == "movecard" then
			room:askForQiaobian(player, room:getAlivePlayers(), self:objectName(), "@huxun-move", true, true)
		end
	end,
}

yuancongusecard = sgs.CreateOneCardViewAsSkill{
	name = "yuancongusecard",
	response_pattern = "@@yuancongusecard",
	response_or_use = true,
	view_filter = function(self, to_select)
		return to_select:isAvailable(sgs.Self) and not to_select:isEquipped()
	end, 
    view_as = function(self, originalCard) 
		return originalCard
	end,
}

yuancong = sgs.CreateTriggerSkill{
	name = "yuancong",
    can_trigger = function(self, event, room, player, data)
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		return false
	end,
}

yuancongother = sgs.CreateTriggerSkill{
	name = "#yuancong-other",
	events = {sgs.EventPhaseEnd},
	frequency = sgs.Skill_Compulsory,
    can_trigger = function(self, event, room, player, data)
		if player and player:isAlive() and player:getPhase() == sgs.Player_Play and not player:isNude() and player:getMark("Global_DamageTimes_Phase") == 0 then
			local skill_list = {}
			local name_list = {}
			local skill_owners = room:findPlayersBySkillName("yuancong")
			for _, skill_owner in sgs.qlist(skill_owners) do
				if skillTriggerable(skill_owner, "yuancong") and skill_owner:hasShownSkill("yuancong") and player:isFriendWith(skill_owner) then
					table.insert(skill_list, self:objectName())
					table.insert(name_list, skill_owner:objectName())
				end
			end
			return table.concat(skill_list,"|"), table.concat(name_list,"|")
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data, skill_owner)
		local cards = room:askForExchange(player, "yuancong_give", 1, 0, "@yuancong:" .. skill_owner:objectName())
		if not cards:isEmpty() then
			local log = sgs.LogMessage()
			log.type = "#InvokeOthersSkill"
			log.from = player
			log.to:append(skill_owner)
			log.arg = "yuancong"
			room:sendLog(log)
			room:broadcastSkillInvoke("yuancong", skill_owner)
            room:notifySkillInvoked(skill_owner, "yuancong")
			room:doAnimate(1, player:objectName(), skill_owner:objectName())
			
			local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_GIVE, player:objectName(), skill_owner:objectName(), "yuancong", "")
		    local move = sgs.CardsMoveStruct(cards, skill_owner, sgs.Player_PlaceHand, reason)
		    room:moveCardsAtomic(move, false)
			
			return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, skill_owner)
		if skill_owner:isAlive() then
			room:askForUseCard(skill_owner, "@@yuancongusecard", "@yuancong-usecard", -1, sgs.Card_MethodUse, false)
		end
		return false
	end,
}

chengpu:addSkill(huxun)
chengpu:addSkill(yuancong)
chengpu:addSkill(yuancongother)

xiliang:insertRelatedSkills("yuancong", "#yuancong-other")

if not sgs.Sanguosha:getSkill("yuancongusecard") then skills:append(yuancongusecard) end


sgs.LoadTranslationTable{
	
    ["#chengpu"] = "Hổ Thủ",
    ["chengpu"] = "Trình Phổ",
	["illustrator:chengpu"] = "Zero",
	["designer:chengpu"] = "Mộng Yểm Cuồng Triều",
    ["huxun"] = "Hổ Huân",
    [":huxun"] = "Khi 1 người kết thúc lượt, nếu trong lượt này có người tiến vào trạng thái hấp hối do bạn gây sát thương, bạn có thể chọn 1 mục:\n1. Nếu bạn không phải người duy nhất có giới hạn máu cao nhất, bạn tăng 1 giới hạn máu và hồi 1 máu;\n2. Bạn có thể di chuyển 1 lá trên bàn chơi.",
    ["yuancong"] = "Nguyên Tòng",
    [":yuancong"] = "Khi kết thúc giai đoạn ra bài của 1 người cùng thế lực với bạn, nếu trong giai đoạn này họ không gây sát thương, họ có thể giao 1 lá cho bạn, sau đó bạn có thể sử dụng 1 lá.",
    
    ["huxun:gainmaxhp"] = "Tăng giới hạn máu",
    ["huxun:movecard"] = "Di chuyển 1 lá trên bàn chơi.",
    ["@huxun-move"] = "Hổ Huân: Có thể di chuyển 1 lá trên bàn chơi.",
    ["@yuancong"] = "Có thể phát động »Nguyên Tòng« của %src",
    ["@yuancong-usecard"] = "Nguyên Tòng: Có thể sử dụng 1 lá trên tay.",

	["cv:chengpu"] = "Thiên Vũ Duyên Vân",
	["$huxun1"] = "某必报三世之恩遇，誓保孙氏之基业！",
	["$huxun2"] = "满腔热血，洒遍了六郡之土！",
	["$yuancong1"] = "取我长矛，老夫今日再奋身一战！",
	["$yuancong2"] = "若无诸君勠力，某安得尺寸之功？",
	["~chengpu"] = "汝等叛逆之贼，安敢索命于我！啊……",
}

-- quancong will be add later
quancong:addSkill("qinzhong")
quancong:addSkill("zhaofu")

sgs.LoadTranslationTable{

	["#quancong"] = "Mộ Thế Diệu Tộc",
    ["quancong"] = "Toàn Tông",
	["designer:quancong"] = "Cẩm Phàm Du Hiệp_Cam",
	["illustrator:quancong"] = "Tiểu Tiểu Kê Tử",
    ["qinzhong"] = "Thân Trùng",
    [":qinzhong"] = "Phó tướng kỹ: Sau khi bắt đầu lượt, bạn có thể hoán đổi phó tướng của bạn với 1 người cùng thế lực với bạn.",
    ["zhaofu"] = "Chiêu Phụ",
    [":zhaofu"] = "• Khi bắt đầu giai đoạn ra bài, nếu tổng số [Thưởng] của tất cả người khác < 3, bạn có thể bỏ 1 lá và chọn 1 người khác, họ tăng 1 [Thưởng].\n• Sau khi lá cơ bản/công cụ phổ thông do người có [Thưởng] sử dụng kết toán xong, bạn có thể lệnh họ giảm 1 [Thưởng], xem như bạn sử dụng lá đó.",

    ["reward"] = "Thưởng",
    
    ["qinzhong-invoke"] = "Có thể phát động »Thân Trùng«, hoán đổi phó tướng với 1 người cùng thế lực.",
    ["@zhaofu1"] = "Có thể phát động »Chiêu Phụ«, bỏ 1 lá để 1 người được nhận [Thưởng]",
    ["zhaofu:prompt"] = "Có thể phát động »Chiêu Phụ«, xem như sử dụng [%arg]",
    ["@zhaofu2"] = "Có thể phát động »Chiêu Phụ«, xem như sử dụng [%arg]",

	["cv:quancong"] = "Thủy Thương Túc",
	["$qinzhong1"] = "功成而不居，以明臣节，以为士范。",
	["$qinzhong2"] = "伏惟至尊累加宠用，臣诚惶诚恐！",
	["$zhaofu1"] = "市米渔利，有何所急？所急扶危济难也。",
	["$zhaofu2"] = "远近英才，皆入吾之网罘矣！",
	["~quancong"] = "名贵一时，忠诚一世，吾生已无憾矣……",
}

qushi = sgs.CreateTriggerSkill{
	name = "qushi",
	events = {sgs.CardFinished, sgs.EventPhaseChanging, sgs.SlashMissed},
	frequency = sgs.Skill_Compulsory,
	on_record = function(self, event, room, player, data)
		if event == sgs.EventPhaseChanging then
			local change = data:toPhaseChange()
			if change.from == sgs.Player_Play then
				room:setPlayerMark(player, "##qushi", 0)
			end
		end
		if event == sgs.SlashMissed then
			local effect = data:toSlashEffect()
			if effect.slash then
				room:setCardFlag(effect.slash, "GlobalSlashMissed")
			end
		end
	end,
    can_trigger = function(self, event, room, player, data)
		if event == sgs.CardFinished and skillTriggerable(player, self:objectName()) and player:getPhase() == sgs.Player_Play then
			local use = data:toCardUse()
			if use.card:isKindOf("Slash") and use.card:hasFlag("GlobalSlashMissed") then
				return self:objectName()
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		local invoke = false
		if player:hasShownSkill(self:objectName()) then
			invoke = true
			room:sendCompulsoryTriggerLog(player, self:objectName())
		else
		    invoke = player:askForSkillInvoke(self, data)
		end
		if invoke then
			room:broadcastSkillInvoke(self:objectName(), player)
            return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
        room:addPlayerMark(player, "#qushi")
        return false
	end,
}

qushitarget = sgs.CreateTargetModSkill{
	name = "#qushi-target",
	pattern = "Slash",
	residue_func = function(self, player)
		return player:getMark("#qushi")
	end,
	extra_target_func = function(self, player)
		return player:getMark("#qushi")
	end,
}

yanxingSummonCard = sgs.CreateArraySummonCard{
	name = "yanxing",
    mute = true,
}

yanxingVS = sgs.CreateArraySummonSkill{
	name = "yanxing",
	array_summon_card = yanxingSummonCard,
}

yanxing = sgs.CreateTriggerSkill{
	name = "yanxing",
	is_battle_array = true,
	battle_array_type = sgs.Formation,
	view_as_skill = yanxingVS,
	can_preshow = false,
    can_trigger = function(self,event,room,player,data)
		return ""
	end,
}

yanxingdistance = sgs.CreateDistanceSkill{
	name = "#yanxing-distance" ,
	correct_func = function(self, from, to)
		local sib = from:getAliveSiblings()
		sib:append(from)
		local teammates = from:getFormation()
		if sib:length() < 4 or teammates:length() < 2 then return 0 end
		local x = 0
		for _, p in sgs.qlist(teammates) do
			if p:hasShownSkill("yanxing") then
				x = x - teammates:length() + 1
			end
		end
		return x
	end
}

yicong = sgs.CreateTriggerSkill{
	name = "yicong",
	relate_to_place = "head",
	events = {sgs.NonTrigger},
    can_trigger = function(self, event, room, player, data)
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		return false
	end,
}

yicongother = sgs.CreateTriggerSkill{
	name = "#yicong-other",
	events = {sgs.CardFinished},
	frequency = sgs.Skill_Compulsory,
    can_trigger = function(self, event, room, player, data)
		if player and player:isAlive() then
			local use = data:toCardUse()
			if use.card:isKindOf("Slash") and use.card:hasFlag("GlobalSlashMissed") and room:isAllOnPlace(use.card, sgs.Player_PlaceTable) then
				local skill_list = {}
				local name_list = {}
				local skill_owners = room:findPlayersBySkillName("yicong")
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skillTriggerable(skill_owner, "yicong") and skill_owner:hasShownSkill("yicong") and player:isFriendWith(skill_owner) and player ~= skill_owner then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
				return table.concat(skill_list,"|"), table.concat(name_list,"|")
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data, skill_owner)
		if room:askForChoice(player, "yicong", "yes+no", data, "@yicong-choose:" .. skill_owner:objectName()) == "yes" then
			local log = sgs.LogMessage()
			log.type = "#InvokeOthersSkill"
			log.from = player
			log.to:append(skill_owner)
			log.arg = "yicong"
			room:sendLog(log)
			room:broadcastSkillInvoke("yicong", skill_owner)
            room:notifySkillInvoked(skill_owner, "yicong")
			return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data, skill_owner)
		local use = data:toCardUse()
		if use.card and room:isAllOnPlace(use.card, sgs.Player_PlaceTable) then
			skill_owner:obtainCard(use.card)
		end
		return false
	end,
}


gongsunzan:addSkill(qushi)
gongsunzan:addSkill(qushitarget)
gongsunzan:addSkill(yanxing)
gongsunzan:addSkill(yanxingdistance)
gongsunzan:addSkill(yicong)
gongsunzan:addSkill(yicongother)

xiliang:insertRelatedSkills("qushi", "#qushi-target")
xiliang:insertRelatedSkills("yanxing", "#yanxing-distance")
xiliang:insertRelatedSkills("yicong", "#yicong-other")


sgs.LoadTranslationTable{
	
	["#gongsunzan"] = "Bạch Mã Tướng Quân",
	["gongsunzan"] = "Công Tôn Toản",
	["illustrator:gongsunzan"] = "Tượng Nhân Hội",
	["designer:gongsunzan"] = "Mộng Yểm Cuồng Triều",
	["qushi"] = "Khu Thỉ",
	[":qushi"] = "Tỏa định kỹ: Giai đoạn ra bài của bạn, sau khi lá [Sát] do bạn sử dụng kết toán xong, nếu [Sát] này đã bị triệt tiêu, bạn lệnh giới hạn sử dụng [Sát] và số mục tiêu của [Sát] do bạn sử dụng trong giai đoạn này +1.",
	["yanxing"] = "Nhạn Hàng",
	[":yanxing"] = "Trận pháp kỹ: Quan hệ đội hình: Nếu bạn có trong quan hệ đội hình, khoảng cách từ người cùng đội hình với bạn đến người khác -X (X là số người khác có cùng đội hình với bạn).",
	["yicong"] = "Nghĩa Tòng",
	[":yicong"] = "Chủ tướng kỹ, Giảm 0.5 máu gốc: Sau khi lá [Sát] do người khác có cùng thế lực với bạn sử dụng kết toán xong, nếu [Sát] này đã bị triệt tiêu, họ có thể lệnh bạn thu lấy [Sát] này.",
	["@yicong-choose"] = "Có thể phát động »Nghĩa Tòng« của %src để họ thu lấy [Sát] này",

	["$yicong1"] = "Lính xếp thành hàng, chỉ có tiến chứ không có lùi",
	["$yicong2"] = "Ngựa no cỏ, lính đã sẵn giao, giờ chỉ đợi lúc ra trận thôi",
	["$qushi1"] = "Cưỡi ngựa phi nhanh, tập kích hậu viện của địch",
	["$qushi2"] = "Kỵ binh tinh nhuệ, chặn đứt địch hậu!",
	["~gongsunzan"] = "Giấc mộng bá chủ Hoàng Đồ, vậy là tan thành mây khói....",
}

haokui = sgs.CreatePhaseChangeSkill{
	name = "haokui",
	on_record = function(self, event, room, player, data)
		if player:getPhase() == sgs.Player_NotActive then
			room:setPlayerMark(player, "##haokui", 0)
		end
	end,
	can_trigger = function(self, event, room, player)
		if skillTriggerable(player, self:objectName()) and player:getPhase() == sgs.Player_Play then
			return self:objectName()
		end
		return ""
	end,
	on_cost = function(self, event, room, player)
		if player:askForSkillInvoke(self:objectName()) then
			room:broadcastSkillInvoke(self:objectName(), player)
            return true
		end
		return false
	end,
	on_phasechange = function(self, player)
		player:drawCards(2, self:objectName())
		player:getRoom():addPlayerMark(player, "##haokui")
		return false
	end,
}

haokuieffect = sgs.CreateTriggerSkill{
	name = "#haokui-effect",
	events = {sgs.CardsMoveOneTime, sgs.EventPhaseEnd},
    can_trigger = function(self, event, room, player, data)
		if not player or player:isDead() or player:getMark("##haokui") == 0 or player:getPhase() ~= sgs.Player_Discard then return "" end
		if event == sgs.CardsMoveOneTime then
			local move_datas = data:toList()
			for _, move_data in sgs.qlist(move_datas) do
				local move = move_data:toMoveOneTime()
				if move.to_place == sgs.Player_DiscardPile then
					for _, id in sgs.qlist(move.card_ids) do
						if room:getCardPlace(id) == sgs.Player_DiscardPile then
							return self:objectName()
						end
					end
				end
			end
		end
		if event == sgs.EventPhaseEnd and not player:hasFlag("haokuiInvoked") then
			return self:objectName()
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		return true
	end,
    on_effect = function(self, event, room, player, data)
        if event == sgs.CardsMoveOneTime then
			local ids = {} 
			local move_datas = data:toList()
			for _, move_data in sgs.qlist(move_datas) do
				local move = move_data:toMoveOneTime()
				if move.to_place == sgs.Player_DiscardPile then
					for _, id in sgs.qlist(move.card_ids) do
						if room:getCardPlace(id) == sgs.Player_DiscardPile then
							table.insert(ids, id)
						end
					end
				end
			end
			if #ids > 0 then
				local all_players = room:getAlivePlayers()
				local to_choose = sgs.SPlayerList()
				for _, p in sgs.qlist(all_players) do
				    if not p:isFriendWith(player) and p:isBigKingdomPlayer() then
						to_choose:append(p)
					end
			    end
				if to_choose:isEmpty() then
					local x = 0
					for _, p in sgs.qlist(all_players) do
						if not p:isFriendWith(player) and p:getHp() >= x then
							if p:getHp() > x then
								x = p:getHp()
								to_choose = sgs.SPlayerList()
							end	
							to_choose:append(p)
						end
					end
					
				end
				if not to_choose:isEmpty() then
					local to = room:askForPlayerChosen(player, to_choose, "haokui_give", "@haokui-give")
					if to then
						local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_GIVE, player:objectName(), to:objectName(), "haokui","")
						local dummy = sgs.Sanguosha:cloneCard("slash", sgs.Card_NoSuit, 0)
						for _, id in ipairs(ids) do
							dummy:addSubcard(id)
						end
						room:obtainCard(to, dummy, reason)
						room:setPlayerFlag(player, "haokuiInvoked")
					end
				end
			end
		end
		if event == sgs.EventPhaseEnd then
			if player:getGeneral():ownSkill("haokui") and player:hasShownAllGenerals() then
                if room:askForChoice(player, "haokui_hide", "yes+no", data, "@haokui-hide1") == "yes" then
                    player:hideGeneral()
                end
            end
			if player:getGeneral2() and player:getGeneral2():ownSkill("haokui") and player:hasShownAllGenerals() then
                if room:askForChoice(player, "haokui_hide", "yes+no", data, "@haokui-hide2") == "yes" then
                    player:hideGeneral(false)
                end
            end
			if player:getMark("haokuitransformUsed") == 0 then
				local all_players = room:getAlivePlayers()
				local to_choose = sgs.SPlayerList()
				for _, p in sgs.qlist(all_players) do
				    if p:isFriendWith(player) and p:canTransform() then
						to_choose:append(p)
					end
			    end
				if not to_choose:isEmpty() then
					local to = room:askForPlayerChosen(player, to_choose, "haokui_transform", "@haokui-transform", true)
                    if to and room:askForChoice(to, "transform_haokui", "yes+no", data, "@transform-ask:::haokui") == "yes" then
                        room:addPlayerMark(player, "haokuitransformUsed")
                        room:transformDeputyGeneral(to)
					end
				end
			end
		end
        return false
	end,
}

xushi = sgs.CreateTriggerSkill{
	name = "xushi",
	events = {sgs.TargetConfirming},
    can_trigger = function(self, event, room, player, data)
		if skillTriggerable(player, self:objectName()) and not player:hasShownSkill(self:objectName()) then
			local use = data:toCardUse()
			if use.card:getTypeId() ~= sgs.Card_TypeSkill and use.from ~= player and use.to:contains(player) then
				for _,p in sgs.qlist(use.to) do
				    if p ~= player then
						return ""
					end
				end
				return self:objectName()
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		if player:askForSkillInvoke(self:objectName()) then
			room:broadcastSkillInvoke(self:objectName(), player)
            return true
		end
		return false
	end,
    on_effect = function(self, event, room, player, data)
        local use = data:toCardUse()
        sgs.Room_cancelTarget(use, player)
		data:setValue(use)
		if use.from and use.from:isAlive() then
			room:askForDiscard(use.from, "xushi_discard", 1, 1, false, true)
		end
        return false
	end,
}

chendeng:addSkill(haokui)
chendeng:addSkill(haokuieffect)
chendeng:addSkill(xushi)
xiliang:insertRelatedSkills("haokui", "#haokui-effect")

sgs.LoadTranslationTable{
	
    ["#chendeng"] = "Hồ Hải Hào Khí",
    ["chendeng"] = "Trần Đăng",
	["illustrator:chendeng"] = "Dật Danh",
	["designer:chendeng"] = "Mộng Yểm Cuồng Triều",
    ["haokui"] = "Hào Khôi",
    [":haokui"] = "Khi bắt đầu giai đoạn ra bài, bạn có thể rút 2 lá;\n▶ Sau khi có bài tiến vào chồng bài bỏ trong giai đoạn bỏ bài lượt này, bạn đem những lá này giao cho 1 người thế lực khác bạn, ưu tiên theo thứ tự sau:\n* Người thuộc đại thế lực;\n* Người có số máu lớn nhất trong số những người thế lực xác định khác bạn;\n▶ Trước khi kết thúc lượt này, nếu bạn không giao bài cho người khác bởi kỹ năng này, bạn thực hiện lần lượt:\n- Nếu bạn đã mở tất cả tướng, bạn có thể úp tướng này;\n- Bạn có thể chọn 1 người cùng thế lực với bạn, họ có thể đổi Phó tướng.",
    ["xushi"] = "Hư Thực",
    [":xushi"] = "Khi bạn trở thành mục tiêu duy nhất của bài do người khác sử dụng, nếu tướng này đang úp, bạn có thể phát động kỹ năng này, thực hiện lần lượt:\n- Hủy bỏ mục tiêu đối với bạn;\n- Bạn lệnh người sử dụng bỏ 1 lá.",
	
    ["@haokui-give"] = "Hào Khôi: Chọn 1 người nhận bài bỏ từ chồng bài bỏ",
    ["@haokui-transform"] = "Hào Khôi: Bạn có thể chọn 1 người cùng thế lực và lệnh họ đổi phó tướng",
    ["@haokui-hide1"] = "Hào Khôi: Bạn có thể úp chủ tướng",
    ["@haokui-hide2"] = "Hào Khôi: Bạn có thể úp phó tướng",
    ["@xushi-discard"] = "Xushi: Có thể bỏ 1 lá của %dest",

	["$haokui1"] = "Trù hoạch thủy lợi nông vụ, đều vì bách tính Từ Châu.",
	["$haokui2"] = "Dưỡng kỳ dục cô, thị dân như thương, dĩ phong định Từ Châu",
	["$xushi1"] = "Ai là hổ, ai là ưng, với ta đều chỉ như quân cờ trên bàn cả",
	["$xushi2"] = "Liệu đoạn khấu đồ, thi sách dĩ trở",
	["~chendeng"] = "Không còn nguyên hóa, mệnh ta chỉ đến thế là cùng....",
}

jiange = sgs.CreateOneCardViewAsSkill{   
	name = "jiange",
	response_or_use = true,
	view_filter = function(self, card)
		if card:getTypeId() == sgs.Card_TypeBasic then return false end
		if sgs.Sanguosha:getCurrentCardUseReason() == sgs.CardUseStruct_CARD_USE_REASON_PLAY then
			local slash = sgs.Sanguosha:cloneCard("slash", sgs.Card_SuitToBeDecided, -1)
			slash:addSubcard(card:getEffectiveId())
			slash:deleteLater()
			return slash:isAvailable(sgs.Self)
		end
		return true
	end,
	view_as = function(self, card)
		local slash = sgs.Sanguosha:cloneCard("slash", card:getSuit(), card:getNumber())
		slash:addSubcard(card:getId())
		slash:setSkillName(self:objectName())
		slash:setShowSkill(self:objectName())
		return slash
	end,
	enabled_at_play = function(self, player)
		return sgs.Slash_IsAvailable(player)
	end, 
	enabled_at_response = function(self, player, pattern)
		return pattern == "slash"
	end
}

qianxueselect = sgs.CreateViewAsSkill{
	name = "qianxueselect",
	expand_pile = "#qianxue",
	response_pattern = "@@qianxueselect",
	view_filter = function(self, selected, to_select)
		if #selected < sgs.Self:getMark("qianxuecount") then
			local ids = sgs.Self:getPile("#qianxue")
			if not ids:contains(to_select:getId()) then return false end
			if to_select:getTypeId() == sgs.Card_TypeBasic then
				for _, id in sgs.qlist(ids) do
					local c2 = sgs.Sanguosha:getCard(id)
					if c2:getTypeId() ~= sgs.Card_TypeBasic and not table.contains(selected, c2) then
						return false
					end
				end
			end
			return true
		end
		return false
	end, 
    view_as = function(self, cards)
		if #cards == 0 then return nil end
		for _,card in ipairs(cards) do
			if card:getTypeId() == sgs.Card_TypeBasic then
				local ids = sgs.Self:getPile("#qianxue")
				for _, id in sgs.qlist(ids) do
					local c2 = sgs.Sanguosha:getCard(id)
					if c2:getTypeId() ~= sgs.Card_TypeBasic and not table.contains(cards, c2) then
						return nil
					end
				end
				break
			end
		end
		
		local skillcard = MemptyCard:clone()
		for _,card in ipairs(cards) do
			skillcard:addSubcard(card)
		end
		return skillcard
	end,
}

qianxue = sgs.CreateTriggerSkill{
	name = "qianxue",
	events = {sgs.EventPhaseChanging, sgs.ConfirmMoveCards},
	relate_to_place = "head",
    can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		if event == sgs.EventPhaseChanging then
		    local change = data:toPhaseChange()
		    if change.to == sgs.Player_NotActive then
			    local discardpile = room:getTag("GlobalRoundDisCardPile"):toList()
				local can_trigger_cheak = false
				for _, card_data in sgs.qlist(discardpile) do
					local card_id = card_data:toInt()
					if room:getCardPlace(card_id) == sgs.Player_DiscardPile and not sgs.Sanguosha:getCard(card_id):isKindOf("ThreatenEmperor") then
						can_trigger_cheak = true
						break
					end
				end
				if can_trigger_cheak then
					local skill_owners = room:findPlayersBySkillName(self:objectName())
					for _, skill_owner in sgs.qlist(skill_owners) do
						if skillTriggerable(skill_owner, self:objectName()) and (skill_owner:hasFlag("GlobalLoseAllHandCards") or
						        skill_owner:hasFlag("GlobalLoseAllEquips") or skill_owner:hasFlag("GlobalLoseAllDelayedTricks")) then
							table.insert(skill_list, self:objectName())
							table.insert(name_list, skill_owner:objectName())
						end
					end
				end
		    end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
    on_cost = function(self, event, room, p, data, player)
		local x = 0
		if player:hasFlag("GlobalLoseAllHandCards") then
			x = x + 1
		end
		if player:hasFlag("GlobalLoseAllEquips") then
			x = x + 1
		end
		if player:hasFlag("GlobalLoseAllDelayedTricks") then
			x = x + 1
		end
		if player:askForSkillInvoke(self:objectName(), sgs.QVariant("invoke:::" .. tostring(x))) then
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, p, data, player)
		local x = 0
		if player:hasFlag("GlobalLoseAllHandCards") then
			x = x + 1
		end
		if player:hasFlag("GlobalLoseAllEquips") then
			x = x + 1
		end
		if player:hasFlag("GlobalLoseAllDelayedTricks") then
			x = x + 1
		end
		if x == 0 then return false end
		local cards = sgs.IntList()
		local discardpile = room:getTag("GlobalRoundDisCardPile"):toList()
		for _, card_data in sgs.qlist(discardpile) do
			local card_id = card_data:toInt()
			if room:getCardPlace(card_id) == sgs.Player_DiscardPile and not sgs.Sanguosha:getCard(card_id):isKindOf("ThreatenEmperor") then
				cards:append(card_id) 
			end
		end
		if cards:isEmpty() then return false end
		room:setPlayerMark(player, "qianxuecount", x)
        room:notifyMoveToPile(player, cards, "qianxue", sgs.Player_PlaceTable, true, true)
        local to_get = room:askForCard(player, "@@qianxueselect", "@qianxue-select:::" .. tostring(x), data, sgs.Card_MethodNone)
        room:setPlayerMark(player, "qianxuecount", 0)
        room:notifyMoveToPile(player, cards, "qianxue", sgs.Player_PlaceTable, false, false)

        if to_get:subcardsLength() > 0 then
            room:obtainCard(player, to_get, true)
        end
		
	end,
}

zhuhu = sgs.CreateTriggerSkill{
	name = "zhuhu",
	events = {sgs.DeathFinished, sgs.GeneralTransformed},
	frequency = sgs.Skill_Compulsory,
    can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}

		local zhuhuTriggerable = function(splayer)
			if not skillTriggerable(splayer, "zhuhu") then return false end
			if splayer:getActualGeneral1():ownSkill("zhuhu") then
				return not splayer:getActualGeneral2():isDoubleKingdoms()
			end
			return splayer:getActualGeneral2():ownSkill("zhuhu")
		end

		if event == sgs.DeathFinished and zhuhuTriggerable(player) then
		    local death = data:toDeath()
			if death.who and death.who:isFriendWith(player) then
				table.insert(skill_list, self:objectName())
				table.insert(name_list, player:objectName())
		    end
		elseif event == sgs.GeneralTransformed then
			local skill_owners = room:findPlayersBySkillName(self:objectName())
			for _, skill_owner in sgs.qlist(skill_owners) do
				if zhuhuTriggerable(skill_owner) and skill_owner:isFriendWith(player) then
					table.insert(skill_list, self:objectName())
					table.insert(name_list, skill_owner:objectName())
				end
			end
			
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
    on_cost = function(self, event, room, p, data, player)
		local invoke = false
		if player:hasShownSkill(self:objectName()) then
			invoke = true
			room:sendCompulsoryTriggerLog(player, self:objectName())
		else
		    invoke = player:askForSkillInvoke(self, data)
		end
		if invoke then
			room:broadcastSkillInvoke(self:objectName(), player)
            return true
		end
		return false
	end,
    on_effect = function(self, event, room, p, data, player)
		if player:getActualGeneral1():ownSkill("zhuhu") then
            room:exchangeHeadAndDeputyGeneral(player)
        elseif player:getActualGeneral2():ownSkill("zhuhu") and player:isChained() then
            room:setPlayerProperty(player, "chained", sgs.QVariant(false))
		end
		if player:canTransform() then
			room:transformDeputyGeneral(player)
		end
	end,
}

shitao:addSkill(jiange)
shitao:addSkill(qianxue)
shitao:addSkill(zhuhu)

if not sgs.Sanguosha:getSkill("qianxueselect") then skills:append(qianxueselect) end

sgs.LoadTranslationTable{
	
    ["#shitao"] = "Đồng Tiến Cộng Thoái",
    ["shitao"] = "Thạch Thao",
	["illustrator:shitao"] = "Dật Danh",
	["designer:shitao"] = "Mộng Yểm Cuồng Triều",
    ["jiange"] = "Kiếm Ca",
    [":jiange"] = "Bạn có thể chuyển hóa sử dụng/đánh ra lá phi cơ bản thành [Sát].",
    ["qianxue"] = "Tiềm Học",
    [":qianxue"] = "Chủ tướng kỹ, Giảm 0.5 máu gốc: Khi 1 người kết thúc lượt, bạn có thể thu lấy tối đa X lá trong những lá đã tiến vào chồng bài bỏ trong lượt này (X là số vùng của bạn mà đã mất đi lá cuối cùng trong lượt này);\n▶ Bạn cần ưu tiên thu lấy những lá phi cơ bản trước;\n▶ Bạn không thể thu lấy [Hiệp Thiên Tử Dĩ Lệnh Chư Hầu].",
    ["zhuhu"] = "Trục Cốc",
    [":zhuhu"] = "Tỏa định kỹ: Sau khi người cùng thế lực với bạn đổi Phó tướng hoặc trận vong, bạn thực hiện lần lượt:\n- Nếu vị trí của tướng này là:\n * Chủ tướng: Bạn hoán đổi Chủ tướng và Phó tướng\n * Phó tướng: Bạn thoát khỏi trạng thái xích;\n- Bạn đổi Tướng này.",
    ["qianxue:invoke"] = "Có thể phát động »Tiềm Học«, thu lấy tối đa %arg lá tiến vào chồng bài bỏ lượt này (ưu tiên lá phi cơ bản)",
    ["@qianxue-select"] = "Tiềm học: Chọn tối đa %arg lá, ưu tiên phi cơ bản.",
    ["#qianxue"] = "Tiềm Học",

	["cv:shitao"] = "Thủy Thương Túc",
	["$jiange1"] = "Đã cầm kiếm là phải quyết tâm, đoạn tuyệt với đời",
	["$jiange2"] = "Ngô chí bất hảo thiên lý tài, duy nguyện trảm tận bách lý hung",
	["$qianxue1"] = "Học đến giờ vẫn chưa thấy đã, phải tốn thêm tiền rồi!",
	["$qianxue2"] = "Nguyên Trực, đoạn này nên giải thế nào?",
	["$zhuhu1"] = "Nguyên Trực đã đi, mỗ cũng cáo từ",
	["$zhuhu2"] = "Loạn lạc rồi sẽ biến mất, mọi chuyện sẽ lại yên bình. Huynh đệ ai cũng có, nhưng liệu có được như bằng hữu?",
	["~shitao"] = "Cùng người hận địch, cùng người giết địch, cũng cùng người đi xuống!",
}

xiaolian = sgs.CreateTriggerSkill{
	name = "xiaolian",
	can_preshow = false,
    can_trigger = function(self, event, room, player, data)
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		return false
	end,
}

xiaoliancompulsory = sgs.CreateTriggerSkill{
	name = "#xiaolian-compulsory",
	events = {sgs.GeneralShowed, sgs.GeneralRemoved},
	frequency = sgs.Skill_Compulsory,
    can_trigger = function(self, event, room, player, data)
		if event == sgs.GeneralShowed then
			if player:cheakSkillLocation("xiaolian", data) and player:getMark("xiaolianUsed") == 0 then
                return self:objectName()
			end
		end
		if event == sgs.GeneralRemoved then
			local remove_data = data:toString():split(":")
			if #remove_data == 2 and table.contains(remove_data[2]:split("+"), "xiaolian") then
                return self:objectName()
			end
		end
		return ""
	end,
    on_cost = function(self, event, room, player, data)
		room:sendCompulsoryTriggerLog(player, "xiaolian")
        room:broadcastSkillInvoke("xiaolian", player)
        if event == sgs.GeneralShowed then
            room:addPlayerMark(player, "xiaolianUsed")
		end
        return true
	end,
    on_effect = function(self, event, room, player, data)
		if event == sgs.GeneralShowed then
			room:askForQiaobian(player, room:getAlivePlayers(), "xiaolian", "@xiaolian-move", true, false)
		end
		if event == sgs.GeneralRemoved then
			local friends = sgs.SPlayerList()
			for _, p in sgs.qlist(room:getAlivePlayers()) do
				if player:isFriendWith(p) then
					friends:append(p)
				end
			end
			if not friends:isEmpty() then
				room:sortByActionOrder(friends)
				for _, p in sgs.qlist(friends) do
					if p:isAlive() then
						p:drawCards(1, "xiaolian")
					end
				end
			end
		end
	end,
}

kangkai = sgs.CreateTriggerSkill{
	name = "kangkai",
	events = {sgs.TargetConfirmed},
    can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		local use = data:toCardUse()
		if use.card and use.card:isKindOf("Slash") then
			local skill_owners = room:findPlayersBySkillName(self:objectName())
			for _, skill_owner in sgs.qlist(skill_owners) do
				if skillTriggerable(skill_owner, self:objectName()) and skill_owner:isFriendWith(player) and skill_owner:ownSkill(self:objectName()) then
					table.insert(skill_list, self:objectName())
					table.insert(name_list, skill_owner:objectName())
				end
			end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
    on_cost = function(self, event, room, target, data, player)
		local source_data = sgs.QVariant()
		source_data:setValue(target)
		if player:askForSkillInvoke(self:objectName(), source_data) then
			room:broadcastSkillInvoke(self:objectName(), player)
			player:removeGeneral(player:inHeadSkills(self:objectName()))
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, player, data, source)		
		if source:isDead() then return false end
		local target = room:askForPlayerChosen(source, room:getAlivePlayers(), "kangkai_target", "@kangkai-target")
		if target then
			room:acquireSkill(target, "feiying_caoang", true, false)
            room:addPlayerMark(target, "##kangkai")
			if target ~= source then
				local recover = sgs.RecoverStruct()
				recover.who = source
				room:recover(target, recover)
				if target:isChained() then
					room:setPlayerProperty(target, "chained", sgs.QVariant(false))
				end
			end
		end
	end,
}

feiying_caoang = sgs.CreateDistanceSkill{
	name = "feiying_caoang" ,
	correct_func = function(self, from, to)
		if to:hasShownSkill(self) then
			return 1
		end
		return 0
	end
}


caoang:addSkill(xiaolian)
caoang:addSkill(xiaoliancompulsory)
xiliang:insertRelatedSkills("xiaolian", "#xiaolian-compulsory")
caoang:addSkill(kangkai)

if not sgs.Sanguosha:getSkill("feiying_caoang") then skills:append(feiying_caoang) end

sgs.LoadTranslationTable{

	["#caoang"] = "Hiếu Chiến Sinh Tử",
	["caoang"] = "Tào Ngang",
	["illustrator:caoang"] = "Zero",
	["designer:caoang"] = "Mộng Yểm Cuồng Triều",
	["xiaolian"] = "Hiếu Liêm",
	[":xiaolian"] = "Tỏa định kỹ:\n• Sau khi mở tướng này lần đầu, bạn phát động kỹ năng này, bạn có thể di chuyển 1 trang bị trên bàn chơi.\n• Sau khi tướng này bị loại bỏ, người cùng thế lực với bạn rút 1 lá.",
	["kangkai"] = "Khảng Khái",
	[":kangkai"] = "Sau khi 1 người cùng thế lực với bạn trở thành mục tiêu của [Sát], bạn có thể loại bỏ tướng này, thực hiện lần lượt:\n- Chọn 1 người, lệnh họ nhận kỹ năng »Phi Ảnh«;\n- Nếu người đó không phải là bạn, người đó hồi 1 máu và thoát trạng thái xích.",
	["feiying_caoang"] = "Phi Ảnh",
	["@kangkai-target"] = "Khảng Khái: Chọn 1 người nhận kỹ năng »Phi Ảnh«",
	["@xiaolian-move"] = "Hiếu Liêm: Bạn có thể di chuyển 1 trang bị trên bàn",
	--曹昂
	["$xiaolian1"] = "Điển tướng quân, hãy xem ai giết địch nhiều hơn nào!",
	["$xiaolian2"] = "Tên phản tặc ngươi, đến một ta giết một!",
	["$kangkai1"] = "Phụ thân lên ngựa, hài nhi sẽ đi theo sau.",
	["$kangkai2"] = "Phụ thân chạy mau, con sẽ đoạn hậu!",
	["~caoang"] = "Phụ thân đã an toàn rồi....",
}

nizhan = sgs.CreateTriggerSkill{
	name = "nizhan",
	events = {sgs.EventPhaseChanging, sgs.ConfirmMoveCards},
    can_trigger = function(self, event, room, player, data)
		local skill_list = {}
		local name_list = {}
		if event == sgs.EventPhaseChanging and player and player:isAlive() then
		    local change = data:toPhaseChange()
		    if change.to == sgs.Player_NotActive then
				local skill_owners = room:findPlayersBySkillName(self:objectName())
				for _, skill_owner in sgs.qlist(skill_owners) do
					if skillTriggerable(skill_owner, self:objectName()) and player ~= skill_owner and
							(skill_owner:hasFlag("GlobalLoseAllHandCards") or skill_owner:getCardUsedTimes("Jink+Nullification") > 0) then
						table.insert(skill_list, self:objectName())
						table.insert(name_list, skill_owner:objectName())
					end
				end
		    end
		end
		return table.concat(skill_list,"|"), table.concat(name_list,"|")
	end,
    on_cost = function(self, event, room, target, data, player)
		local source_data = sgs.QVariant()
		source_data:setValue(target)
		if player:askForSkillInvoke(self:objectName(), source_data) then
			room:broadcastSkillInvoke(self:objectName(), player)
			return true
		end
		return false
		
	end,
    on_effect = function(self, event, room, target, data, player)		
		local choices = {}
		if player:canSlash(target, false) then
			table.insert(choices, "slash")
		end
		if player:canGetCard(target, "he") then
			table.insert(choices, "extraction")
		end
		if #choices == 0 then return false end
        local choice = room:askForChoice(player, self:objectName(), table.concat(choices,"+"), data, "@nizhan-choose::" .. target:objectName(), "extraction+slash")
		if choice == "extraction" then
			local card_id = room:askForCardChosen(player, target, "he", self:objectName(), false, sgs.Card_MethodGet)
			local reason = sgs.CardMoveReason(sgs.CardMoveReason_S_REASON_EXTRACTION, player:objectName())
			room:obtainCard(player, sgs.Sanguosha:getCard(card_id), reason, false)
		elseif choice == "slash" then
			local slash = sgs.Sanguosha:cloneCard("slash", sgs.Card_NoSuit, 0)
			slash:setSkillName("_nizhan")
			room:useCard(sgs.CardUseStruct(slash, player, target), false)
		end
	end,
}

nizhaneffect = sgs.CreateTriggerSkill{
	name = "#nizhan-effect",
	events = {sgs.TargetChosen},
	can_trigger = function(self, event, room, player, data)
		if not player or player:isDead() then return "" end
		local use = data:toCardUse()
		if use.card and use.card:isKindOf("Slash") and use.card:getSkillName() == "nizhan" then
			local target = use.to:at(use.index)
			if target and target:isAlive() then
				return self:objectName() .. ":" .. target:objectName()
			end
		end
	end,
    on_cost = function(self, event, room, target, data, player)
		return true
	end,
	on_effect = function(self, event, room, target, data, player)
		local use = data:toCardUse()
		
		local log = sgs.LogMessage()
		log.type = "#NizhanEffect"
		log.from = player
		log.to:append(target)
		room:sendLog(log)
		
		target:addQinggangTag(use.card)
		
		return false
	end,
}

sunhuan:addSkill(nizhan)
sunhuan:addSkill(nizhaneffect)
xiliang:insertRelatedSkills("nizhan", "#nizhan-effect")

sgs.LoadTranslationTable{
	["#sunhuan"] = "Tông Thất Nhan Uyên",
	["sunhuan"] = "Tôn Hoàn",
	["illustrator:sunhuan"] = "Thinking",
	["designer:sunhuan"] = "Mộng Yểm Cuồng Triều",
	["nizhan"] = "Nghịch Trảm",
	[":nizhan"] = "Trước khi kết thúc lượt của người khác, nếu bạn đã triệt tiêu lá bài do họ sử dụng trong lượt này hoặc bạn đã mất đi lá cuối cùng trên tay, bạn có thể chọn 1 mục:\n1. Bạn thu lấy 1 lá của họ;\n2. Bạn xem như sử dụng 1 [Sát] với họ;\n▶ Sau khi bạn xác định mục tiêu của [Sát] này, ứng với mỗi mục tiêu, bạn vô hiệu phòng cụ của họ đến khi xác định số sát thương cuối cùng mà họ phải nhận.",

	["@nizhan-choose"] = "Nghịch Trảm: Chọn 1 hiệu ứng cho %dest",
	["nizhan:extraction"] = "Thu 1 lá",
	["nizhan:slash"] = "Xem như sử dụng [Sát]",

	["#NizhanEffect"] = "%from đã vô hiệu phòng cụ của %to",
	
	["cv:sunhuan"] = "Tịch Kính Jnrio",
    ["$nizhan1"] = "诸位莫急，守住此城即为大功一件！",
	["$nizhan2"] = "玄德公，战场上还识得我么？！",
    ["~sunhuan"] = "此坞未就，桓愧对主公………" ,
	
}

sgs.Sanguosha:addSkills(skills)

return {xiliang}