return {
	----N001
	["taiga"] = "逢坂大河", 
	["&taiga"] = "逢坂大河", 
	["#taiga"] = "掌中萌虎", 
	["#&taiga"] = "龙与虎", 
	["~taiga"] = "让....人火大啊", 
	["designer:taiga"] = "hm",
	["cv:taiga"] = "釘宮理恵",
	["illustrator:taiga"] = "30637291",

	["huxiao"] = "虎啸",
	[":huxiao"] = "Chủ tướng kỹ, giảm 0.5 máu gốc: Sau khi bạn nhận sát thương, bạn có thể +1 giới hạn máu.",	

	["yexi"] = "夜袭",
	[":yexi"] = "Khi bắt đầu giai đoạn chuẩn bị, bạn có thể xem X lá trên đầu chồng bài rút (X là số máu bạn đã mất), sắp xếp tùy ý những lá này lên đầu hoặc xuống đáy chồng bài rút, sau đó bạn chọn 1 mục:\n1. Đặt giới hạn máu của bạn thành số máu hiện tại, sau đó rút X lá;\n2. Phó tướng kỹ: Bỏ X lá trên tay bạn, sau đó hồi đầy máu.",	
	["@yexi-discard"] = "你需弃置已损失体力值张数的牌，以发动“夜袭②”",
	["maxhptohp"] = "将体力上限调整至你当前体力值",
	["hptomaxhp"] = "将体力值调整至体力上限",
	["#Yeximaxhptohp"] = "%from 发动了 “<font color=\"yellow\"><b>夜袭</b></font>”，将体力上限从 %arg 调整到了 %arg2",
	["#Yexihptomaxhp"] = "%from 发动了 “<font color=\"yellow\"><b>夜袭</b></font>”，将体力从 %arg2 调整到了 %arg",

	----N002
	["shana"] = "夏娜", 
	["&shana"] = "夏娜", 
	["#shana"] = "炎发灼眼的讨伐者", 
	["#&shana"] = "灼眼的夏娜", 
	["~shana"] = "为什么，为什么，为什么你现在要说这些...", 
	["designer:shana"] = "钉子",
	["cv:shana"] = " 釘宮理恵",
	["illustrator:shana"] = "40322063",

	["duanzui"] = "断罪",
	[":duanzui"] = "Một lần trong giai đoạn ra bài, bạn có thể chuyển hoá sử dụng 1 trang bị thành [Hỏa Sát], [Sát] này có thể chỉ định thêm 1 mục tiêu, không tính vào số lần sử dụng.",

	["honglian"] = "红莲",
	[":honglian"] = "Sau khi bạn mất 1 lá trong vùng trang bị hoặc nhận sát thương thuộc tính, bạn có thể rút 1 lá.",
	
	----N003
	["louise"] = "露易丝·瓦利埃尔", 
	["&louise"] = "露易丝", 
	["#louise"] = "零之露易丝", 
	["#&louise"] = "零之使魔", 
	["~louise"] = "才人，才人，救我", 
	["designer:louise"] = "hm",
	["cv:louise"] = "釘宮理恵",
	["illustrator:louise"] = "55470621",

	["lingjie"] = "零界",
	[":lingjie"] = "Một lần trong giai đoạn ra bài, bạn có thể chọn 1 người không trong trạng thái xích, lệnh tất cả người cùng thế lực với bạn và họ nhận trạng thái xích;\n-> Bạn rút bài bằng chênh lệnh số người giữa 2 thế lực, tối đa 3 lá.",
	["#LingjieChain"] = "%from 的 “%arg” 生效，横置了 %to",

	["xuwu"] = "虚无",
	[":xuwu"] = "出牌阶段，或每当你受到一次伤害后，你可以重铸一张装备牌，然后若你的装备区里没有牌，你摸一张牌。",
	["@xuwu-recast"] = "请选择一张装备牌，重铸之",
	["~xuwu"] = "选择一张装备牌→点击确定",

	--["bianchi"] = "鞭笞",
	--[":bianchi"] = "出牌阶段限一次，你可以对一名攻击范围内的其他角色造成一点伤害，然后令其摸X张牌（X为该角色失去的体力值）。若该角色因此而进入濒死阶段，将你的武将牌叠置。",	
	
	----N004
	["aria"] = "神崎·H·亚里亚", 
	["&aria"] = "亚里亚", 
	["#aria"] = "双枪双剑", 
	["#&aria"] = "绯弹的亚里亚", 
	["~aria"] = "不要啊，不要啊，金次", 
	["designer:aria"] = "hm",
	["cv:aria"] = "釘宮理恵",
	["illustrator:aria"] = "19981312",

	["jingdi"] = "敬敌",
	[":jingdi"] = "出牌阶段，你可以横置副将的武将牌，然后弃置此回合内未以此法指定过的一名其他势力的角色的一张牌。",
	-- [":jingdi"] = "出牌阶段限一次，你可以将一张手牌中的非连横牌交给一名对你造成过伤害的角色，然后你摸一张牌。",	

	["wujie"] = "武戒",
	[":wujie"] = "每当你使用点数为偶数的牌时，你可以重置或横置一名角色副将的武将牌。",
	["@wujie-targetchoose"] = "你可以发动“武戒”：选择一名角色，将其副将的武将牌横置/重置",
	["#WujieChain"] = "%from 发动了 “%arg”，将 %to 副将的武将牌横置",
	["#WujieUnchain"] = "%from 发动了 “%arg”，将 %to 副将的武将牌重置",
	-- [":wujie"] = "每轮每名角色限一次，你造成或受到伤害时，若该伤害值不小于目标的体力值，伤害来源可以令目标回复一点体力，然后伤害来源获得一个额外的出牌阶段。",
	-- ["@wujie_used"] = "武戒已用",

	----N005
	["holo"] = "赫萝", 
	["&holo"] = "赫萝", 
	["#holo"] = "贤狼", 
	["#&holo"] = "狼与香辛料",
	["~holo"] = "真是的，怎么这么傻", 
	["designer:holo"] = "昂翼天使",
	["cv:holo"] = "小清水亜美",
	["illustrator:holo"] = "8890195",

	["jisui"] = "稷穗",
	[":jisui"] = "Một lần trong giai đoạn ra bài, bạn có thể chọn tuỳ ý người khác có thế lực xác định khác nhau, thực hiện lần lượt:\n- Lật bài từ chồng bài rút bằng số người còn sống;\n- Bạn và họ có thể hoán đổi 1 lá trên tay với 1 lá trong những lá đã lật;\n- Bạn chọn 1 mục:\n1. Đưa tất cả lá đã lật vào chồng bài bỏ;\n2. Đặt tất cả lá đã lật về chồng bài rút, sau đó xem như sử dụng [Ngũ Cốc Phong Đăng]",
	["@jisui-exchange"] = "你可以选择一张手牌确定，然后选择“稷穗”展示的一张牌交换",
	["#JisuiSwapCard"] = "%to 用手牌里的【%arg】与 %from 发动的 “<font color=\"yellow\"><b>稷穗</b></font>” 中的 “%arg2” 交换",
	["useag"] = "将这些牌置于牌堆顶，视为使用一张【五谷丰登】",
	["discardput"] = "将这些牌置入弃牌堆",

	----N006
	["eru"] = "千反田爱瑠", 
	["&eru"] = "千反田爱瑠", 
	["#eru"] = "千金大小姐", 
	["#&eru"] = "冰菓", 
	["~eru"] = "", 
	["designer:eru"] = "hmqgg",
	["cv:eru"] = "佐藤聡美",
	["illustrator:eru"] = "official pics",

	["haoqi"] = "好奇",
	[":haoqi"] = "Một lần trong giai đoạn ra bài, bạn có thể giao 1 nửa (làm tròn xuống) lá trên tay cho 1 người khác, lệnh họ chọn 1 mục:\n1. Giao cho bạn 1 nửa (làm tròn lên) lá trên tay họ;\n2. Mở tất cả tướng;\n3. Thay đổi trạng thái chồng tướng.",
	["halfcards"] = "交给对方一半（向上取整）手牌",
	["showallgenerals"] = "明置两张武将牌",
	["turnoverself"] = "将武将牌叠置",
	["@haoqi-halfcards"] = "请选择你的一半的（向上取整）手牌，交给对方",

	["jinzhi"] = "进制",
	[":jinzhi"] = "Giai đoạn rút bài, bạn có thể không rút bài, tiến hành phán xét, sau đó lặp lại đến khi kết quả phán xét của bạn có điểm <= kết quả phán xét trước, sau đó thu lấy tất cả kết quả phán xét.",	

	----N007
	["ruri"] = "五更琉璃", 
	["&ruri"] = "五更琉璃", 
	["#ruri"] = "堕天圣黑猫", 
	["#&ruri"] = "我的妹妹不可能这么可爱！", 
	["~ruri"] = "", 
	["designer:ruri"] = "hmqgg",
	["cv:ruri"] = "花澤香菜",
	["illustrator:ruri"] = "815086240",

	["dushe"] = "毒舌",
	[":dushe"] = "Giai đoạn ra bài, bạn có thể chuyển hoá sử dụng [Sát] thành [Quá Hạ Sách Kiều];\n->Sau khi bạn chỉ định mục tiêu cho [Quá Hạ Sách Kiều] này, bạn có thể lệnh tất cả người trong tầm đánh của bạn trở thành mục tiêu.",	
	["$dushe"] = "",

	----N008
	["a_azusa"] = "小豆梓", 
	["&a_azusa"] = "小豆梓", 
	["#a_azusa"] = "小豆子", 
	["#&a_azusa"] = "变态王子与不笑猫。", 
	["~a_azusa"] = "为什么要欺骗别人呢，别再跟我说话了", 
	["designer:a_azusa"] = "hmqgg",
	["cv:a_azusa"] = "石原夏織",
	["illustrator:a_azusa"] = "38191081",

	["weihao"] = "伪壕",
	[":weihao"] = "Giai đoạn ra bài, nếu giới hạn trữ bài của bạn > 0, bạn có thể -1 giới hạn trữ bài trong lượt này, rút 1 lá.",
	
	["zhuyi"] = "属意",
	[":zhuyi"] = "Giai đoạn ra bài, bạn có thể đặt 1 trang bị trên tay bạn vào vùng trang bị của người khác, giới hạn trữ bài của bạn +1 trong lượt này.",
	["$ZhuyiEquip"] = "%from 被装备了 %card",
	
	["@weihao"] = "伪壕",
	["@zhenhao"] = "真壕",

	----N009
	["rikka"] = "小鸟游六花", 
	["&rikka"] = "小鸟游六花", 
	["#rikka"] = "邪王真眼", 
	["#&rikka"] = "中二病也要谈恋爱！",
	["~rikka"] = "", 
	["designer:rikka"] = "hmqgg",
	["cv:rikka"] = "内田真礼",
	["illustrator:rikka"] = "42201199",

	["fangzhurikka"] = "放逐",
	[":fangzhurikka"] = "Sau khi bạn nhận sát thương, ứng với mỗi sát thương, bạn có thể lệnh 1 người khác rút X lá (X là số máu bạn đã mất, tối đa 3), sau đó lệnh họ thay đổi trạng thái chồng tướng.",
	["fangzhu_rikka-invoke"] = "你可以发动“放逐”<br/> <b>操作提示</b>: 选择一名其他角色→点击确定<br/>",

	["xieyu"] = "邪域",
	[":xieyu"] = "Trận pháp kỹ: Quan hệ đội hình: Người cùng đội hình với bạn sử dụng công cụ phổ thông phân loại chỉ định đơn mục tiêu có thể chỉ định thêm 1 mục tiêu.",
	["xieyu-target"] = "邪域",

	----N010
	["yukino"] = "Yukinoshita Yukino", 
	["&yukino"] = "Yukinoshita Yukino", 
	["#yukino"] = "冰之女王", 
	["#&yukino"] = "我的青春恋爱物语果然有问题", 
	["~yukino"] = "", 
	["designer:yukino"] = "hmqgg",
	["cv:yukino"] = "小倉唯",
	["illustrator:yukino"] = "55305971",

	["duran"] = "独然",
	[":duran"] = "Toả định kỹ:\n** Khoảng cách từ người có số máu >= bạn đến bạn +1.\n** Khoảng cách từ người có giới hạn máu >= bạn đến bạn +1;\n** Khi bắt đầu giai đoạn ra bài, bạn rút X lá (X là số thế lực không có bạn trong tầm đánh).",
	["#DuranCounter"] = "%from 发动“%arg2”，攻击范围内没有 %from 的其他势力有 %arg 个",
	["#duran-dis"] = "独然",

	["jieao"] = "Kiệt Ngạo",
	[":jieao"] = "Toả định kỹ: Trước khi bạn chấp hành thưởng phạt, lệnh người vừa trận vong trở thành Dã tâm gia.",
	
	----N011
	["y_yui"] = "由比滨结衣", 
	["&y_yui"] = "由比滨结衣",
	["#y_yui"] = "团子", 
	["#&y_yui"] = "我的青春恋爱物语果然有问题",
	["~y_yui"] = "", 
	["designer:y_yui"] = "钉子",
	["cv:y_yui"] = "东山奈央",
	["illustrator:y_yui"] = "34938515",

	["xianli"] = "鲜丽",
	[":xianli"] = "主将技，此武将牌上单独的阴阳鱼个数-1。出牌阶段限一次，你可以选择一名有暗置武将牌的角色，然后令其选择一项：1、令你摸一张牌；2、明置一张武将牌并弃置一张牌。",
	["drawonecard"] = "令来源摸一张牌",
	["showonegeneral"] = "明置一张武将牌并弃置一张牌",
	["@xianli-askdiscard"] = "受到“鲜丽”的影响，请选择一张牌弃置",

	["yuanxin"] = "援心",
	[":yuanxin"] = "一名角色的结束阶段开始时，若你于此回合内回复了体力，你可以失去1点体力，然后令一名其他角色回复1点体力。若如此做，你摸两张牌。",
	["@yuanxin_choosetarget"] = "请选择“援心”的目标角色",

	----N012
	["mikoto"] = "御坂美琴", 
	["&mikoto"] = "御坂美琴", 
	["#mikoto"] = "超电磁炮", 
	["#&mikoto"] = "某科学的超电磁炮", 
	["~mikoto"] = "救救我。。。", 
	["designer:mikoto"] = "钉子",
	["cv:mikoto"] = "佐藤利奈",
	["illustrator:mikoto"] = "36171150",

	["dianji"] = "电击",
	[":dianji"] = "弃牌阶段结束时，若你于此回合内没有使用过【杀】，你可以将你的武将牌叠置，然后对一名角色造成1点雷电伤害。",
	["@dianji_target"] = "“电击”生效，请选择一名角色对其造成1点雷电伤害",

	["cichang"] = "磁场",
	[":cichang"] = "每当一名角色叠置其武将牌后，若其处于“叠置状态”，你可以弃置一张基本牌，令其平置其武将牌，然后若你弃置的牌为火【杀】或雷【杀】，你可以令两名角色横置其副将的武将牌；若你弃置的牌为【桃】或【酒】，你摸两张牌。",
	["@cichang_discard"] = "你可以弃置一张基本牌，发动“磁场”",
	["@cichang_choosetarget"] = "请选择两名角色，将这些角色横置",
	["#CichangTurnFaceUp"] = "%from 发动了 “%arg”，将 %to 的武将牌平置了",
	["#CichangTurnFaceDown"] = "%from 发动了 “%arg”，将 %to 的武将牌叠置了", -- its face down status
	["#CichangChain"] = "%from 发动了 “%arg”，将 %to 的武将牌横置了",

	----N013
	["ruiko"] = "佐天泪子", 
	["&ruiko"] = "佐天泪子", 
	["#ruiko"] = "第四波动", 
	["#&ruiko"] = "某科学的超电磁炮", 
	["~ruiko"] = "", 
	["designer:ruiko"] = "御坂2623",
	["cv:ruiko"] = "伊藤かな恵",
	["illustrator:ruiko"] = "9854031",

	-- ["xianqun"] = "掀裙",
	-- [":xianqun"] = "出牌阶段限一次，你可以指定一名装备区里有牌的其他角色，你将该角色装备区里的一张牌置于其武将牌上，称为“裙”。该角色的下个回合结束后，将“裙”置入该角色的装备区里。",	
	-- ["ruiko_qun"] = "裙",
	-- ["$Xianqun_back"] = "%from 的“%arg”被触发， %arg2 的%card被置入装备区。",

	["kongli"] = "空力",
	[":kongli"] = "每当一名角色叠置其武将牌后处于“叠置状态”，或横置副将的武将牌后，你可以令其摸一张牌，每回合对每名角色限一次。",

	["hefeng"] = "和风",
	[":hefeng"] = "每名角色的回合限一次，每当你需要使用一张【桃】时，你可以将至少一张手牌当【桃】使用，令你的手牌数为全场最少（或之一）。",

	----N014
	["asuna"] = "结城明日奈", 
	["&asuna"] = "亚丝娜", 
	["#asuna"] = "闪光",
	["#&asuna"] = "刀剑神域",
	["~asuna"] = "对不起...永别了...", 
	["designer:asuna"] = "Sword Elucidator",
	["cv:asuna"] = "戸松遥",
	["illustrator:asuna"] = "47371333",

	["shanguang"] = "闪光",
	[":shanguang"] = "** Sau khi bạn nhận sát thương, bạn có thể lệnh nguồn sát thương đặt 1 lá lên tướng này, gọi là [Thước].\n** Giới hạn trữ bài của bạn +X (X là số [Thước]).",

	["zhuanyu"] = "馔玉",
	[":zhuanyu"] = "Một lần trong giai đoạn ra bài, bạn có thể đưa 1 [Thước] vào chồng bài bỏ, rút 2 lá.",
	["shuo"] = "Thước",

	----N015
	["hitagi"] = "战场原黑仪", 
	["&hitagi"] = "战场原黑仪", 
	["#hitagi"] = "冷傲之蟹", 
	["#&hitagi"] = "<物语>系列",
	["~hitagi"] = "", 
	["designer:hitagi"] = "Sword Elucidator",
	["cv:hitagi"] = "斎藤千和",
	["illustrator:hitagi"] = "6693976",

	["qingyou"] = "倾诱",
	[":qingyou"] = "每当你受到伤害后，你可以令伤害来源摸一张牌，然后手牌数少于伤害来源的角色各弃置其一张牌。",

	["baoyan"] = "暴言",
	[":baoyan"] = "出牌阶段限一次，你可以交给一名其他角色一张【杀】，然后摸一张牌。",

	["zhongxie"] = "重蟹",
	[":zhongxie"] = "锁定技，若你的两张武将牌均明置，且：\n1、有单独的阴阳鱼，将“倾诱”的描述“令伤害来源”改为“令你和伤害来源各”。\n2、没有单独的阴阳鱼，将“暴言”的描述“出牌阶段限一次”改为“出牌阶段”。",

	----N016
	["watashi"] = "人类小姐", 
	["&watashi"] = "人类小姐", 
	["#watashi"] = "我", 
	["#&watashi"] = "人类衰退之后", 
	["~watashi"] = "那就这样吧，再见", 
	["designer:watashi"] = "钉子",
	["cv:watashi"] = "中原麻衣",
	["illustrator:watashi"] = "28552580",

	["tiaoting"] = "调停",
	[":tiaoting"] = "结束阶段开始时，你可以指定两名势力不同的其他角色，若如此做，直到你的下个回合开始，其中一名角色对另一名角色第一次造成伤害时，防止之，然后这些角色各摸一张牌。",
	["@tiaoting-targetchoose"] = "你可以发动“调停”，指定两名势力不同的其他角色",
	["~tiaoting"] = "点击两名势力不同的其他角色->点击确定",
	["#TiaotingArmistice"] = "%from 发动了 “%arg”，指定了 %to",
	["#TiaotingNoDamage"] = "%from 发动了 “%arg”，%to 之间造成的第一次伤害将被防止，且各摸一张牌。",

	["jilu"] = "记录",
	[":jilu"] = "“调停”指定的角色的结束阶段开始时，若于此回合内你没有发动“调停”，你可摸一张牌。",

	----N017
	["haruhi"] = "涼宮春日", 
	["&haruhi"] = "涼宮春日", 
	["#haruhi"] = "团长大人", 
	["#&haruhi"] = "凉宫春日的忧郁", 
	["~haruhi"] = "", 
	["designer:haruhi"] = "钉子",
	["cv:haruhi"] = "平野綾",
	["illustrator:haruhi"] = "46397378",

	["zhizun"] = "至尊",
	[":zhizun"] = "锁定技，若此武将牌明置，你所属的势力成为唯一的大势力。",

	["gexin"] = "革新",
	[":gexin"] = "出牌阶段，若上个进行回合的角色不为你，你可以将一张黑色牌当【挟天子以令诸侯】使用。",

	----N018
	["yuki"] = "长门有希", 
	["&yuki"] = "长门有希", 
	["#yuki"] = "资讯统合思念体", 
	["#&yuki"] = "凉宫春日的忧郁", 
	["~yuki"] = "", 
	["designer:yuki"] = "钉子",
	["cv:yuki"] = "茅原実里",
	["illustrator:yuki"] = "10414653",

	["zixun"] = "资讯",
	[":zixun"] = "锁定技，摸牌阶段，你改为摸X张牌（X为你此武将明置的回合数，且至多为3）。",
	["@zixun"] = "资讯",

	["tonghe"] = "统合",
	[":tonghe"] = "副将技，此武将牌上单独的阴阳鱼个数-1。出牌阶段限一次，你可以令与你距离为一的角色和与其势力相同的角色各弃置一张牌，如果该势力为大势力，则你令这些角色各摸一张牌。",
	["@tonghe_discard"] = "受到“统合”的影响，你需要弃置一张牌",

}