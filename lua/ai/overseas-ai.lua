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
--海外版专属

--卑弥呼
local guishu_skill = {}
guishu_skill.name = "guishu"
table.insert(sgs.ai_skills, guishu_skill)
guishu_skill.getTurnUseCard = function(self)
    local spadecards = {}
    local cards = self.player:getHandcards()
    for _, id in sgs.qlist(self.player:getHandPile()) do
        cards:prepend(sgs.Sanguosha:getCard(id))
    end
	cards = sgs.QList2Table(cards)
	self:sortByUseValue(cards, true)
    for _, card in ipairs(cards) do
		if card:getSuit() == sgs.Card_Spade then
            table.insert(spadecards, card)
        end
    end
    if #spadecards == 0 then
        return
    end
    local trickcards = {"befriend_attacking","known_both"}--有优先顺序
    table.removeOne(trickcards, self.player:property("guishuprohibit"):toString())
    if trickcards[1] == "known_both" and self:getUseValue(spadecards[1]) > sgs.ai_use_value.KnownBoth then
        return--#spadecards < 2 每回合不重置
    end
    Global_room:writeToConsole("鬼术卡类型:"..trickcards[1])
    return sgs.Card_Parse("@GuishuCard=" ..  spadecards[1]:getEffectiveId() .. ":" .. trickcards[1])
end

sgs.ai_skill_use_func.GuishuCard = function(card, use, self)
	local userstring = card:toString()
	userstring = (userstring:split(":"))[3]
    local guishucard = sgs.cloneCard(userstring, card:getSuit(), card:getNumber())
    guishucard:setCanRecast(false)
    if self.player:isCardLimited(guishucard, sgs.Card_MethodUse) then
        return
    end
    self:useCardByClassName(guishucard, use)--确保能使用
    if use.card then--and use.to and not use.to:isEmpty() 如果有use.to会使用虚拟牌，为何？
		Global_room:writeToConsole("鬼术卡使用:"..userstring)
		use.card = card
	end
end

sgs.ai_use_priority.GuishuCard = sgs.ai_use_priority.BefriendAttacking + 0.1
sgs.ai_use_value.GuishuCard = sgs.ai_use_value.BefriendAttacking

sgs.guishu_suit_value = {
	spade = 3.9
}

sgs.ai_skill_invoke.yuanyu = true

--曹真
sgs.ai_skill_invoke.sidi = function(self, data)
    if not self:willShowForDefence() then
        return false
    end
    local target = data:toPlayer()
    if not self:isFriend(target) then
        return true
    end
    local num = 0
    for _, card in sgs.qlist(target:getHandcards()) do
		if not sgs.cardIsVisible(card, target, self.player)
        or not (isCard("Peach", card, self.player) or (card:isKindOf("Analeptic") and target:getHp() == 1)) then
			num = num + 1
		end
	end
    if self:needToThrowArmor(target) then
        num = num + 1
    end
    if target:getWeapon() and target:getOffensiveHorse() then
        num = num + 1
    end
    if num == 0 or (num < 3 and self.player:getPile("drive"):length() > 4) then
        return false
    end
    return true
end

sgs.ai_skill_exchange.sidi = function(self,pattern,max_num,min_num,expand_pile)
    self.sidi_recover = nil
    self.sidi_skill = nil
    self.sidi_cardtype = nil
    local current = self.room:getCurrent()
    if self:isFriend(current) then
        self:sort(self.friends, "hp")--从小到大排序
        for _, friend in ipairs(self.friends) do
            if friend:getSeemingKingdom() == "wei" and friend:getHp() == 1 then
                self.sidi_recover = true
                return self.player:getPile(expand_pile):first()--"drive"
            end
        end
    end
    if self:isEnemy(current) and (not self:willSkipPlayPhase(current) or self.player:getPile("drive"):length() > 2) then
--禁卡
        if getCardsNum("TrickCard", current, self.player) > (current:hasShownSkill("jizhi") and 1 or 2)
        or (current:hasShownSkills("guose|luanji|guishu") and current:getHandcardNum() > 1)
        or (current:hasShownSkill("jixi") and current:getPile("field"):length() > 1)
        or (current:hasShownSkills("qice|yigui")) then
            self.sidi_cardtype = "TrickCard"
        end
        if current:hasShownSkills("diaodu+xiaoji|diaodu+xuanlue") then
            self.sidi_cardtype = "EquipCard"
        end
        if (current:getHp() == 1 and self:isWeak(current) and current:getMark("GlobalBattleRoyalMode") == 0)
        or ((self:hasCrossbowEffect(current) or current:hasShownSkills(sgs.force_slash_skill))
                and getCardsNum("Slash", current, self.player) >= 1) then
            self.sidi_cardtype = "BasicCard"
        end
        for _, friend in ipairs(self.friends) do
            if current:canSlash(friend, nil, true) and sgs.getDefenseSlash(friend, self) <= 2 then
                self.sidi_cardtype = "BasicCard"
                break
            end
        end
--技能
        local function findskill(skills)
            for _, skill in ipairs(skills:split("|")) do
                if current:hasShownSkill(skill) then
                    return skill
                end
            end
            return nil
        end
        local sidi_firstskills =--注意有优先顺序
                "suzhi|jinghe|miewu|jieyue|jili|tongdu|chuli|wansha|zaoyun|jinfa|yingzi_zhouyu|zhukou|boyan"
        self.sidi_skill = findskill(sidi_firstskills)
        if current:hasShownSkills(sgs.lose_equip_skill.."|diaodu") and (not self.sidi_cardtype or self.sidi_cardtype ~= "EquipCard") then
            
        end
        if current:hasShownSkills("luanji|guose|jixi|qice|yigui|guishu") and (not self.sidi_cardtype or self.sidi_cardtype ~= "TrickCard") then
            self.sidi_skill = findskill("luanji|guose|jixi|qice|yigui|guishu")
        end
        if current:hasShownSkills("paoxiao|kuanggu|kuangcai") and (not self.sidi_cardtype or self.sidi_cardtype ~= "BasicCard") then
            self.sidi_skill = findskill("paoxiao|kuanggu|kuangcai")
        end
        if current:hasShownSkill("hongfa") and current:getPile("heavenly_army"):isEmpty()
        and self.player:getPlayerNumWithSameKingdom("AI", "qun") > 1 then
            self.sidi_skill = "hongfa"
        end
        if current:hasShownSkill("jiahe") and not current:getPile("flame_map"):isEmpty() then
            self.sidi_skill = "jiahe"
        end
        if current:hasShownSkill("zisui") and current:getPile("disloyalty"):length() > 2 then
            self.sidi_skill = "zisui"
        end
        if current:hasShownSkill("xiongnve") and current:getMark("#massacre") > (self:isWeak(current) and 1 or 3) then
            self.sidi_skill = "xiongnve"
        end
        if current:hasShownSkill("paiyi") and current:getPile("power_pile"):length() > 3 then
            self.sidi_skill = "paiyi"
        end
    end
--回复
    local weis = {}
    for _, friend in ipairs(self.friends) do
        if friend:getSeemingKingdom() == "wei" and friend:isWounded() then
            table.insert(weis, friend)
        end
    end
    if #weis > 0 then
        local allweak = true
        for _, p in ipairs(weis) do
            if p:getHp() > 2 then--not self:isWeak(p)
                allweak = false
            end
        end
        if allweak or self.player:getMark("GlobalBattleRoyalMode") > 0 then
            self.sidi_recover = true
        end
    end
    local sidi_max = (self.sidi_recover and 1 or 0) + (self.sidi_skill and 1 or 0) + (self.sidi_cardtype and 1 or 0)
    sidi_max = math.min(sidi_max, self.player:getPile("drive"):length(), max_num)
    local discards = {}
    for _, id in sgs.qlist(self.player:getPile("drive")) do
        if #discards < sidi_max then
            table.insert(discards, id)
        end
    end
    return discards
end

sgs.ai_skill_exchange.sidi_put = function(self,pattern,max_num,min_num,expand_pile)
    local cards = self.player:getCards("he")
	cards = sgs.QList2Table(cards)
    if self.player:getPhase() <= sgs.Player_Play then
		self:sortByUseValue(cards, true)
	else
		self:sortByKeepValue(cards)
	end
    if isCard("Peach", cards[1], self.player) or (cards[1]:isKindOf("Analeptic") and self.player:getHp() == 1) then
        return {}
    end
    return cards[1]:getEffectiveId()
end

sgs.ai_skill_choice["sidi_choice"] = function(self, choices, data)
    --"cardlimit" << "skilllimit" << "recover"
    Global_room:writeToConsole("司敌选择:" .. choices)
    choices = choices:split("+")
    if self.sidi_cardtype and table.contains(choices, "cardlimit") then
        return "cardlimit"
    end
    if self.sidi_skill and table.contains(choices, "skilllimit") then
        return "skilllimit"
    end
    if self.sidi_recover and table.contains(choices, "recover") then
        return "recover"
    end
    return choices[math.random(1, #choices)]
end

sgs.ai_skill_playerchosen["sidi_recover"] = function(self, targets)
    Global_room:writeToConsole("司敌恢复")
    targets = sgs.QList2Table(targets)
    if self:isFriend(targets[1]) then
        self:sort(targets, "hp")
        return targets[1]
    else
        self:sort(targets, "hp", true)
        for _, p in ipairs(targets) do
            if not p:hasShownSkills(sgs.priority_skill) and p:getHp() > 1 then
                return p
            end
        end
        return targets[1]
    end
end

sgs.ai_skill_choice["sidi_skill"] = function(self, choices, data)
    Global_room:writeToConsole("司敌禁用技能选择:" .. choices)
    choices = choices:split("+")
    if self.sidi_skill and table.contains(choices, self.sidi_skill) then
        Global_room:writeToConsole("司敌禁用技能:"..sgs.Sanguosha:translate(self.sidi_skill))
        return self.sidi_skill
    end
    return choices[math.random(1, #choices)]
end

sgs.ai_skill_choice["sidi_cardtype"] = function(self, choices, data)
    --"BasicCard+EquipCard+TrickCard"
    --Global_room:writeToConsole("司敌禁用牌类型选择:" .. choices)
    choices = choices:split("+")
    if self.sidi_cardtype and table.contains(choices, self.sidi_cardtype) then
        Global_room:writeToConsole("司敌禁用牌类型:"..sgs.Sanguosha:translate(self.sidi_cardtype))
        return self.sidi_cardtype
    end
    return choices[math.random(1, #choices)]
end

function sgs.ai_cardneed.sidi(to, card, self)
	return to:getHandcardNum() < 2
end

sgs.ai_need_damaged.sidi = function (self, attacker, player)

end

--廖化
sgs.ai_skill_invoke.dangxian = true

--诸葛瑾
sgs.ai_skill_cardask["@huanshi-card"] = function(self, data)
	if not (self:willShowForAttack() or self:willShowForDefence()) then return "." end
	local judge = data:toJudge()
	local cards = sgs.QList2Table(self.player:getCards("he"))
	for _, id in sgs.qlist(self.player:getHandPile()) do
		table.insert(cards, 1, sgs.Sanguosha:getCard(id))
	end

	if self:needRetrial(judge) then
		local card_id = self:getRetrialCardId(cards, judge)
		if card_id ~= -1 then
			return "$" .. card_id
		end
	end
	return "."
end

function sgs.ai_cardneed.huanshi(to, card, self)
	for _, player in sgs.qlist(self.room:getAllPlayers()) do
		if self:getFinalRetrial(to) == 1 and to:isFriendWith(player) and self:isFriend(player) then
			if player:containsTrick("lightning") then
				return not (card:getSuit() == sgs.Card_Spade and card:getNumber() >= 2 and card:getNumber() <= 9)
			end
			if self:willSkipDrawPhase(player) then
				return card:getSuit() == sgs.Card_Club
			end
			if self:willSkipPlayPhase(player) then
				return card:getSuit() == sgs.Card_Heart
			end
		end
	end
end

sgs.huanshi_suit_value = {
	heart = 3.9,
	club = 2.7
}

local hongyuan_skill = {}
hongyuan_skill.name = "hongyuan"
table.insert(sgs.ai_skills, hongyuan_skill)
hongyuan_skill.getTurnUseCard = function(self)
	if self.player:isKongcheng() or self.player:hasUsed("HongyuanCard") then return end
	return sgs.Card_Parse("@HongyuanCard=.&hongyuan")
--[[使用ViewAsSkill的写法
    local Skill = sgs.Sanguosha:getViewAsSkill("hongyuan")
    if Skill:isEnabledAtPlay(self.player) then
        local hcards = sgs.QList2Table(self.player:getHandcards())
        self:sortByUseValue(hcards, true)
        local cards = sgs.CardList()
        for _, c in ipairs(hcards) do
            if Skill:viewFilter(cards, c) then
                cards:append(c)
            end
        end
        if cards:length() > 0 then
            local hycard = Skill:viewAs(cards)
            Global_room:writeToConsole("弘援合纵:"..hycard:toString())
            return hycard
        end
    end
]]
end

sgs.ai_skill_use_func.HongyuanCard = function(hycard, use, self)
	local targets = sgs.PlayerList()
    local friends = {}
    for _, p in ipairs(self.friends_noself) do
		if hycard:targetFilter(targets, p, self.player)  then
			table.insert(friends, p)
		end
	end
	if #friends > 0 then
        local cards = sgs.QList2Table(self.player:getHandcards())
	    self:sortByUseValue(cards, true)
		local card, friend = self:getCardNeedPlayer(cards, friends, "hongyuan")
		if card and friend then
            use.card = sgs.Card_Parse("@HongyuanCard=" .. card:getId() .. "&hongyuan")
            if use.to then use.to:append(friend) end
            Global_room:writeToConsole("弘援合纵目标:"..sgs.Sanguosha:translate(friend:getGeneralName()).."/"..sgs.Sanguosha:translate(friend:getGeneral2Name()))
            return
		end
	end
end

sgs.ai_use_priority.HongyuanCard = 2
sgs.ai_card_intention.HongyuanCard = -40

sgs.ai_skill_playerchosen.hongyuan = function(self, targets)
	targets = sgs.QList2Table(targets)
    self:sort(targets, "handcard")
    for _, p in ipairs(targets) do
        if p:getHandcardNum() < self.player:getHandcardNum() then
            return p
        end
    end
	return {}
end

sgs.ai_skill_invoke.mingzhe = true

--全琮


--郭淮
sgs.ai_skill_playerchosen.jingce = sgs.ai_skill_playerchosen.damage--选择目标怎样合适？

sgs.ai_skill_choice.startcommand_jingce = sgs.ai_skill_choice.startcommand_to

sgs.ai_skill_choice["docommand_jingce"] = function(self, choices, data)
  local source = data:toPlayer()
  local index = self.player:getMark("command_index")
  local is_enemy = self:isEnemy(source)
  local is_friend = self:isFriend(source)
  if index == 1 then
    if not is_enemy and not is_friend then
      return "yes"
    end
    if is_friend and not self:isWeak(source) then
      for _, p in ipairs(self.enemies) do
        if p:getHp() == 1 and self:isWeak(p) and self:isEnemy(source, p) then
          return "yes"
        end
      end
    end
  end
  if index == 5 and not self.player:faceUp() then
    return "yes"
  end
  if is_enemy then
    if index == 2 then
      return "yes"
    end
    if index == 3 and self.player:hasSkill("hongfa") and not self.player:getPile("heavenly_army"):isEmpty() then
      return "yes"
    end
    if index == 4 then
      if self.player:getMark("command4_effect") > 0 then
        return "yes"
      end
      local has_peach = false
      for _, c in sgs.qlist(self.player:getHandcards()) do
        if isCard("Peach", c, self.player) then--有实体卡桃可回血
          has_peach = true
        end
      end
      if has_peach then
        for _, p in ipairs(self.friends) do
          if p:getHp() == 1 and self:isWeak(p) and source:canSlash(self.player, nil, true) then
            return "no"
          end
        end
      end
      if not source:canSlash(self.player, nil, true) then
        return "yes"
      end
    end
    if index == 6 and self.player:getEquips():length() < 3 and self.player:getHandcardNum() < 3 then
      return "yes"
    end
  end
  return "no"
end

sgs.ai_skill_playerchosen["command_jingce"] = sgs.ai_skill_playerchosen.damage

--杨修
sgs.ai_skill_invoke.danlao = function(self, data)
	local use = data:toCardUse()
    local ucard = use.card
	if ucard:isKindOf("GodSalvation") and self.player:canRecover() then
		return false
    elseif ucard:isKindOf("AmazingGrace") and self:playerGetRound(self.player) < self.room:alivePlayerCount()/2 then
		return false
	elseif ucard:isKindOf("IronChain") and self.player:isChained() then
        return false
    elseif ucard:isKindOf("AwaitExhausted") and self.player:getHandcardNum() > 2
      and self:getCardsNum({"Peach", "Jink"}) == 0 then
        return false
    elseif ucard:isKindOf("AllianceFeast") and use.from == self.player then
        return false
    elseif ucard:isKindOf("Conquering") then
        return false
    elseif ucard:isKindOf("ExNihilo") or ucard:isKindOf("BefriendAttacking") then
        return false
    elseif self:isFriend(use.from) and (ucard:isKindOf("Snatch") or ucard:isKindOf("Dismantlement")) then
        return false
	else
		return true
	end
end

sgs.ai_skill_invoke.jilei = function(self, data)
	local damage = data:toDamage()
	return self:isEnemy(damage.from)
end

sgs.ai_skill_choice.jilei = function(self, choices, data)
	local dfrom = data:toDamage().from
    if (self:hasCrossbowEffect(dfrom) and dfrom:inMyAttackRange(self.player))
		or dfrom:isCardLimited(sgs.cloneCard("ex_nihilo"), sgs.Card_MethodUse, true)
        or (dfrom:getHp() < 2 and getCardsNum("Peach", dfrom, self.player) > 0) then
		return "BasicCard"
	else
		return "TrickCard"
	end
end

--祖茂



--伏完
sgs.ai_skill_invoke.moukui = function(self, data)
    if not self:willShowForAttack() then return false end
	local target = data:toPlayer()
	if self:isFriend(target) then
        return self:needToThrowArmor(target)
    end
    return true
end

sgs.ai_skill_choice.moukui = function(self, choices, data)
	local target = data:toPlayer()
    Global_room:writeToConsole("谋溃目标防御值：" ..sgs.getDefenseSlash(target, self))
    if not self:isFriend(target) and self:getDangerousCard(target) then
        return "discard"
    end
    if self:isFriend(target) and self:needToThrowArmor(target) then
        return "discard"
    end
	if (self:isEnemy(target) and self:doNotDiscard(target)) or sgs.getDefenseSlash(target, self) < 2 then
		return "draw"
	end
	return "discard"
end

--陈到
sgs.ai_skill_invoke.wanglie = function(self, data)
	local ucard = data:toCardUse().card
    local num = 0
    for _, c in ipairs(self:getTurnUse()) do
        if not c:isKindOf("SkillCard") then--转化成普通卡的技能卡？
            num = num + 1
        end
    end
    if num == 0 then--需要配合调整出牌优先度
        return true
    end
    if ucard:isKindOf("Slash") and ucard:hasFlag("drank")
    and (self:getOverflow() <= 1 or num <= 1) then
        return true
    end
    return false
end

--田豫
sgs.ai_skill_invoke.zhenxi = function(self, data)
	local target = data:toPlayer()
    return not self:isFriend(target)
end

sgs.ai_skill_choice.zhenxi = function(self, choices, data)
	local target = data:toPlayer()
    --"usecard"简单写法
	return "discard"
end

sgs.ai_skill_choice.zhenxi_discard = "yes"

sgs.ai_skill_invoke.jiansu = true

--马良


sgs.ai_skill_invoke.naman = true

sgs.ai_skill_playerchosen["naman_target"] = function(self, targets)
    local use = self.player:getTag("NamaneUsedata"):toCardUse()
    local card = use.card
    local from = use.from
    local is_friend = self:isFriend(from)
    local tos = sgs.QList2Table(use.to)
    local targetlist = sgs.QList2Table(targets)

    if card:isKindOf("AwaitExhausted") then
        return {}
    end
    if card:isKindOf("ArcheryAttack") or card:isKindOf("SavageAssault") then
        self:sort(tos, "hp")
        for _, p in ipairs(tos) do
            if self.player:isFriendWith(p) and self:aoeIsEffective(card, p, from) then
                return p
            end
        end
        for _, p in ipairs(tos) do
            if self.player:isFriendWith(p) and self:aoeIsEffective(card, p, from) then
                return p
            end
        end
    end
    if card:isKindOf("GodSalvation") then
        self:sort(tos, "hp")
        for _, p in ipairs(tos) do
            if self:isEnemy(p) and self:trickIsEffective(card, p, from) then
                return p
            end
        end
        for _, p in ipairs(tos) do
            if not self:isFriend(p) and self:trickIsEffective(card, p, from) then
                return p
            end
        end
    end
    if card:isKindOf("AmazingGrace") then
        self:sort(tos, "handcard")
        for _, p in ipairs(tos) do
            if self:isEnemy(p) and self:trickIsEffective(card, p, from) then
                return p
            end
        end
        for _, p in ipairs(tos) do
            if not self:isFriend(p) and self:trickIsEffective(card, p, from) then
                return p
            end
        end
    end
    --连环、戮力同心、调虎离山、联军，考虑使用和目标敌我，太复杂了
end