testCard = sgs.CreateSkillCard{
	name = "testCard",
	will_throw = false,
	filter = function(self, selected, to_select)
		local card_name = sgs.Self:getTag("test"):toString()
		if card_name ~= "" then
			local card = sgs.Sanguosha:cloneCard(card_name)
			card:addSubcards(subcards)
			card:setCanRecast(false)
			card:deleteLater()
			return card:targetFilter(selected, to_select, sgs.Self) and not sgs.Self:isProhibited(to_select, card, selected)
		end
		return false
	end,
	target_fixed = function(self)
		local card_name = sgs.Self:getTag("test"):toString()
		if card_name ~= "" then
			local card = sgs.Sanguosha:cloneCard(card_name)
			card:addSubcards(subcards)
			card:setCanRecast(false)
			card:deleteLater()
			return card:targetFixed()
		end
		return false
	end, 	
	feasible = function(self, selected)
		local card_name = sgs.Self:getTag("test"):toString()
		if card_name ~= "" then
			local card = sgs.Sanguosha:cloneCard(card_name)
			card:addSubcards(subcards)
			card:setCanRecast(false)
			card:deleteLater()
			return card:targetsFeasible(selected, sgs.Self)
		end
		return false
	end,
	on_validate = function(self, cardUse)
		local room = cardUse.from:getRoom()
		local card_name = self:toString():split(":"):last()
		local card = Sanguosha:cloneCard(card_name)
		card:setSkillName("test")
		card:addSubcards(subcards)
		card:deleteLater()
		return card
	end,
	on_validate_in_response = function(self, source)
		local room = source:getRoom()
		local card_name = self:toString():split(":"):last()
		local card = Sanguosha:cloneCard(card_name)
		card:setSkillName("test")
		card:addSubcards(subcards)
		card:deleteLater()
		return card
	end,
}

test = sgs.CreateViewAsSkill{
	name = "test",
	response_or_use = true,
	guhuo_type = "btd",
	view_filter = function(self,cards)
		return true
	end,
	view_as = function(self,cards)
		local card_name = sgs.Self:getTag("test"):toString()
		if card_name ~= "" then
			local card = testCard:clone()
			card:setUserString(card_name)
			card:addSubcard(cards)
			card:setShowSkill(self:objectName())
			return card
		return nil
	end,
	enabled_at_play = function(self, player)
		return player:hasShownSkill(self:objectName())
	end
	enabled_at_response = function(self,player,pattern)
		return player:hasShownSkill(self:objectName())
	end,
	enabled_at_nullification = function(self, player)
		return player:hasShownSkill(self:objectName())
	end

}