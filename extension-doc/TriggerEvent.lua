-- Dưới đây là các event và chính thức hiện có trong game.

TriggerEvent = {
    NonTrigger, -- chỉ dành cho những kỹ năng đặc biệt. mặc định không bao giờ trigger

    GameStart, -- Kỹ năng phát động ở ngay đầu game. Trigger với tất cả người chơi, không data.
    TurnStart, -- Timing đầu tiên của 1 lượt. Thường chỉ dùng để bật chế độ huyến chiến và kiểm tra trạng thái chồng tướng. player trong trigger là người đang vào lượt. Không nên sử dụng timing này, trừ khi muốn làm kỹ năng mà người bị chồng tướng vẫn có thể kích.
    EventPhaseStart, -- Khi bắt đầu 1 giai đoạn. Timing phổ biến của hầu hết kỹ năng đầu giai đoạn nào đó. Player là người chuyển giai đoạn, không có data. Có thể dùng PhaseChangeSkill tương đương với timing này
    EventPhaseProceeding, -- Vui lòng không dùng timing này trừ khi hiểu mình đang làm gì
    EventPhaseEnd, --Khi kết thúc 1 giai đoạn nào đó. Player là người chuyển giai đoạn, không có data.
    EventPhaseChanging, -- Khi đang chuyển giai đoạn. Hạ Hầu Uyên, Trương Cáp sẽ kích ở timing này. Player là người chuyển giai đoạn. Khác với các timing trên, player đang không trong giai đoạn nào, vì vậy muốn lấy thông tin giai đoạn đang chuyển thì phải dùng data, sử dụng data:toPhaseChange(). on effect của timing này nếu return true sẽ khiến giai đoạn bị skip. Tuy nhiên để skip 1 giai đoạn chuẩn, vui lòng dùng cả return true và player:skip(giai đoạn);
    EventPhaseSkipping, -- Trigger nếu 1 giai đoạn bị skip. player và data giống EventPhaseChanging. on effect của timing này nếu return true thì giai đoạn đó diễn ra bình thường

    DrawNCards, --Xảy ra khi 1 người chuẩn bị rút bài ở giai đoạn rút bài. player là người sẽ rút. Dùng data:toInt() để lấy ra số lá hiện tại mà ng đó rút. Nếu là tỏa định kỹ thay đổi số lá rút, nên dùng DrawCardsSkill thay vì TriggerSkill
    AfterDrawNCards, --Sau khi 1 người rút bài trong giai đoạn rút bài. player là người rút. Dùng data:toInt() để lấy ra số lá họ đã rút. Lỗ túc kích ở timing này

    PreHpRecover, -- Khi 1 người chuẩn bị hồi máu. player là người đang được hồi máu. Thông tin hồi máu lấy bằng data:toRecover(). Nếu on effect của timing này return true thì người đó không hồi máu nữa
    HpRecover, --Sau khi 1 người hồi máu. player là người vừa hồi máu, thông tin hồi máu lấy bằng data:toRecover(). Cam phu nhân là ví dụ điển hình.
    PreHpLost, --Khi chuẩn bị tự mất máu. player là người sắp mất máu, số máu mất lấy bằng data:toInt(). Nếu on effect của timing này return true thì người đó không bị mất máu nữa
    HpLost, -- Sau khi tự mất máu. player là người đã mất máu, số máu mất lấy bằng data:toInt(). Timing cuối cùng của quá trình mất máu
    HpChanged, --Sau khi số máu thay đổi, bất kể bởi sát thương, mất máu, hay hồi máu. player là người thay đổi số máu
    MaxHpChanged, --Sau khi giới hạn máu thay đổi. player là người thay đổi giới hạn máu
    PostHpReduced, --Sau khi số máu giảm, bất kể bởi sát thương hay tự máu máu. Timing này dùng để kiểm tra trạng thái hấp hối.  player là người đã giảm máu

    EventLoseSkill, --Khi 1 người mất kỹ năng. player là người mất kỹ năng. Danh sách kỹ năng lấy bằng data:toString(). Cấu trúc string dạng {mã kỹ năng}:{head/deputy} (Không bao gồm {} ). Thường dùng cho những kỹ năng trạng thái như Trâu Thị cấm lật tướng để check việc không còn kỹ năng này nữa.
    EventAcquireSkill, --Khi 1 người nhận kỹ năng. player là người nhận kỹ năng. Danh sách kỹ năng lấy bằng data:toString(). Cấu trúc string dạng {mã kỹ năng}:{head/deputy} (Không bao gồm {} )

    StartJudge, --Khi bắt đầu quá trình phát xét, player là người thực hiện phán xét, sử dụng data:toJudge()
    AskForRetrial, --Quá trình thay đổi phán xét, player lần lượt là tất cả người chơi, sử dụng data:toJudge()
    FinishRetrial, --Sau khi kết thúc quá trình thay đổi phán xét, player là người thực hiện phán xét, sử dụng data:toJudge(). Dự kiến tương lai, nếu on effect mà return true ở timing này sẽ hủy bỏ quá trình phán xét, hiện tại chưa hỗ trợ.
    FinishJudge, --Sau khi kết thúc quá trình phán xét, player là người thực hiện phán xét, sử dụng data:toJudge(). Quách Gia Thiên Đố ở timing này

    PindianVerifying, --Khi kiểm tra lá đấu điểm, player lần lượt là những người tham gia đấu điểm. sử dụng data:toPindian(). Tôn Sách là 1 ví dụ
    Pindian, --Sau khi đấu điểm có hiệu lực. player là nguồn phát động đấu điểm. Sử dụng data:toPindian()

    TurnedOver, --Sau khi thay đổi trạng thái chồng tướng. player là người thay đổi
    ChainStateChanged, --Sau khi thay đổi trạng thái xích. player là người thay đổi
	RemoveStateChanged, --Sau khi thay đổi trạng thái rời bàn chơi (bởi điệu hồ ly sơn). player là người thay đổi. Khương duy cần timing này để khi có người bị điệu hổ khiến cho người trong lượt thay đổi quan hệ đội hình.

    ConfirmDamage, --Timing đầu tiên của quá trình gây sát thương. player là người gây sát thương, sử dụng data:toDamage(). Không xảy ra timing này nếu là sát thương lan xích hoặc chuyển sát thương trực tiếp (tiểu kiều cũ). Thường dùng cho những case thay đổi thuộc tính cơ bản của sát thương:
		-- Chuyển nguồn sát thương (mạnh hoạch).
		-- Xét số sát thương mặc định (Mi Phương, Trương Dực). Các kỹ năng trừ sát thương không nằm ở timing này.
		-- Thay đổi thuộc tính của sát thương. (Trương Lỗ cũ)
	-- Nói cách khác, chỉ dùng làm timing giải quyết, không dùng làm timing để kích các kỹ năng. 

	--kể từ timing dưới đến timing DamageInflicted, nếu có on effect return true sẽ kết thúc quá trình sát thương ngay lập tức, chuyển sang timing DamageComplete
    Predamage, --Timing tiếp theo của quá trình gây sát thương. player là người gây sát thương. sử dụng data:toDamage(). Thường chỉ sử dụng cho quá trình chuyển đổi dạng sát thương mà yêu cầu đã biết số sát thương mặc định, ví dụ âm binh biến sát thương thành tự mất máu.
    DamageForseen, --Timing đầu tiên của người nhận sát thương, diễn ra sau 2 timing trên. player là người nhận sát thương, sử dụng data:toDamage(). Hiện quốc chiến không có kỹ năng ở timing này.
    DamageCaused, --Khi gây sát thương. player là người gây sát thương, sử dụng data:toDamage()
    DamageInflicted, --Khi nhận sát thương. player là người nhận sát thương, data:toDamage()
	--kết thúc những timing nếu on effect return true sẽ dừng kết toán.
    PreDamageDone, --Timing đầu tiên của quá trình mất máu. player là người nhận sát thương, sử dụng data:toDamage(). cuồng cốt của ngụy diên sẽ kiểm tra khoảng cách ở timing này.
    DamageDone, --Vào máu, player là người nhận sát thương, sử dụng data:toDamage(). Không nên sử dụng timing này, chủ yếu game dùng để ghi nhận sát thương, kiểm tra quá trình lan xích... ở cuối timing này
    Damage, --Sau khi gây sát thương, player là người gây sát thương, sử dụng data:toDamage()
    Damaged, --Sau khi nhận sát thương, player là người nhận sát thương, sử dụng data:toDamage()
    DamageComplete, --Sau khi kết thúc quá trình sát thương. player là người nhận, sử dụng data:toDamage(). Timing này luôn xảy ra kể cả sát thương đã bị chặn. Timing này dùng để tạo quá trình lan xích. hoặc nếu muốn làm kỹ năng khi chặn dmg thì có thể dùng timing này.

    Dying, --Khi 1 người tiến vào hấp hối. player lần lượt là tất cả người chơi, sử dụng data:toDying(). Giả hủ cấm đào ở timing này. Nếu on effect return true ở timing này sẽ hủy bỏ timing, những người khác sẽ không đc check timing này.
    QuitDying, --Sau khi kết thục quá trình trạng thái hấp hối. player là người thoát hấp hối, sử dụng data:toDying(). Lưu ý nếu hấp hối chết vẫn có timing này, do đó người chơi cần phải kiểm tra player còn sống nếu cần thiết.
    AskForPeaches, --Khi 1 người trong trạng thái hấp hối, tương đương với timing dùng đào. player lần lượt là tất cả mọi người. sử dụng data:toDying()
    AskForPeachesDone, --Sau khi kết thúc vòng giải quyết hấp hối, player là người hấp hối, sử dụng data:toDying(). Trận vong được diễn ra ở cuối timing này nếu máu người chơi vẫn < 1.

    BeforeGameOverJudge, --Quá trình đầu tiên của trận vong. player là người sẽ chết, sử dụng data:toDeath() cuối timing này, nếu người chơi có tướng chưa mở sẽ bị cưỡng chế lật tướng ở timing này, data:toDeath()
    GameOverJudge, --Quá trình đánh giá game kết thúc chưa, player là người sẽ chết, sử dụng data:toDeath(). nếu có bộc lộ dã tâm thì sẽ diễn ra ở timing này.
    Death, --Khi 1 người trận vong, player là lần lượt tất cả mọi người, bao gồm cả người sẽ chết. sử dụng data:toDeath().
    BuryVictim, --Quá trình trận vong. player là người trận vong, sử dụng data:toDeath(). Timing này chủ yếu dùng để game loại bỏ những gì còn lại của người đó về chồng bài bỏ cũng như update lại chồng tướng thừa, cũng như xử lý thưởng phạt cho người giết. Nếu quân chủ trận vong, những người khác sẽ thanh dã tâm ở cuối timing này.
	DeathFinished, --Sau khi 1 người trận vong. player là lần lượt tất cả người chơi và người vừa chết. sử dụng data:toDeath(). Tôn Lâm thu xác chết ở timing này, không phải timing khi trận vong như bản giấy do vấn đề kỹ thuật. và hoa hùng báo team ở timing này :)))
    GameFinished, --Đừng bao h sử dụng timing này. timing này được tính là exception để kết thúc trận đấu.

    SlashEffected, --khi sát chuẩn bị có hiệu lực. player là người bị sát, sử dụng data:toSlashEffect(). Thường dùng cho các phòng cụ với kỹ năng khiến lá sát không có hiệu quả.
    SlashProceed, --Quá trình xử lý sát, player là người sử dụng sát, sử dụng data:toSlashEffect(). thường dùng để hỏi người chơi sử dụng thiểm, do đó không nên sử dụng timing này.
    SlashHit, --Khi bắt đầu quá trình sát gây sát thương, player là người sử dụng sát, sử dụng data:toSlashEffect(). Thường không sử dụng timing này, nếu bạn muốn chạy sát thương thì hãy dùng timing khi gây sát thương. Game sử dụng timing này để hiện hoạt ảnh là chính, như nụ cười của từ tướng quân
    SlashMissed, --Khi sát đã bị triệt tiêu bởi thiểm, player là người sử dụng sát, sử dụng data:toSlashEffect(). Phá thạch phủ, triệu vân đánh người hay hồi máu ở timing này.
	
	JinkEffect, --Khi bắt đầu hiệu quả của sử dụng Thiểm, player là người sử dụng thiểm, sử dụng data:toCard(). Nếu on effect return true thì thiểm này không có hiệu quả. Hiện không có kỹ năng ở quốc chiến sử dụng timing này.
	
	BeforeCardsMove, --Khi chuẩn bị di chuyển lá bài, hay có thể gọi là khi mất bài. player lần lượt là tất cả người chơi, sử dụng data:toMoveOneTime(). Nếu on effect return true và di chuyển này không phải do luật chơi thì quá trình mất bài dừng lại.
	ConfirmMoveCards, --timing cuối trước khi là bài do chuyển. player lần lượt là tất cả người chơi, sử dụng data:toMoveOneTime(). hiện không sử dụng
	PreCardsMoveOneTime, --timing ngay sau khi là bài đã di chuyển. player lần lượt là tất cả người chơi, sử dụng data:toMoveOneTime(). thường chỉ dùng để ghi chép, hoặc xóa thông tin những lá đặc biệt như lá không hưởng ứng của lưu kì, lá hợp tung của gia cát cẩn. Nếu để kích kỹ năng, hay dùng timing sau.
    CardsMoveOneTime, --Sau khi di chuyển lá bài, hay có thể gọi là sau khi mất bài. player lần lượt là tất cả người chơi, sử dụng data:toMoveOneTime()

    CardAsked, --Khi được yêu cầu sử dụng/đánh ra lá bài có tên cụ thể (thay đổi phán xét k có lá bài cụ thể), player là người được hỏi, data:toStringList().first() để lấy ra tên lá cần sử dụng. Dùng lệnh room:provide(card) để xem như đã sử dụng lá này nếu thỏa mãn điều kiện (cần tạo object card). Hiện tại chỉ có bát quái dùng timing này. Timing này chỉ áp dụng với những lá hưởng ứng như thiểm, không áp dụng với những lá chủ động dùng.
    CardResponded, --Khi đánh ra lá bài. player là người đánh ra, sử dụng data:toCardResponse()

    PreCardUsed, --Timing đầu tiên của quá trình sử dụng lá bài. player là người sử dụng, sử dụng data:toCardUse(). Cần lưu ý kỹ năng chủ động của người chơi thuộc nhóm ViewAsSkill bản chất cũng được xem là sử dụng bài, do đó cần phải kiểm tra type của lá sử dụng có phải là skill không. Thường được sử dụng để đánh dấu là bài cho mục đích gì đó, ví dụ sát của hứa chử lỏa y.
	TargetSelected, -- Timing sau khi tuyên bố sử dụng bài, thường dùng để thêm mục tiêu. player là người sử dụng, data:toCardUse()
    CardUsed, --Khi sử dụng bài. player là người sử dụng bài, sử dụng data:toCardUse(). Chắc khỏi giải thích vì 1 tỉ kỹ năng dùng cái này
	TargetChoosing, --Timing liền sau của timing khi sử dụng bài. player là người sử dụng bài, sử dụng data:toCardUse(). Timing này text lá bài thường là khi người khác sử dụng bài. Mã Lương dùng timing này để thêm bớt mục tiêu.
    TargetConfirming, --Khi trở thành mục tiêu của lá bài. player lần lượt là tất cả mục tiêu của lá bài, sử dụng data:toCardUse(). Trong timing này, nếu có sử thay đổi thêm mục tiêu (đại kiểu), cần tự tạo trigger riêng với người này.
	TargetRecord, -- Chốt danh sách mục tiêu. player là người sử dụng bài, sử dụng data:toCardUse(). Nếu không có gì đặc biệt thì sau timing này, không được phép thay đổi mục tiêu của lá bài nữa, nếu không crash game ráng chịu :)).
	TargetChosen, -- Sau khi xác định mục tiêu của lá bài. sử dụng player là người sử dụng bài, sử dụng data:toCardUse(). trigger nhiều lần ứng với mỗi mục tiêu, sử dụng card_use.to.at(card_use.index) để lấy ra người đang xử lý. Nếu kỹ năng chỉ kích 1 lần cho tất cả mục tiêu thì cần check index == 0.
    TargetConfirmed, --Sau khi trở thành mục tiêu của lá bài. player lần lượt là tất cả mục tiêu của lá bài, data:toCardUse()

    CardEffect, --timing đầu tiên của quá trình hiệu quả lá bài. player là mục tiêu giải quyết hiệu quả, sử dụng data:toCardEffect(). Nếu không có gì đặc biệt, vui lòng không dùng timing này, do nó có mục đích riêng.
    CardEffected, --Khi lá bài bắt đầu có hiệu quả, player là mục tiêu giải quyết hiệu quả, sử dụng data:toCardEffect(). nếu on effect return true ở timing này thì lá bài không có hiểu quả. (ví dụ nguyên đội chống nam man). Vô Giải được hỏi ở cuối timing này.
	CardEffectConfirmed, -- timing cuối cùng trước khi lá bài có hiệu quả. chỉ xảy ra nếu chắc chắn sẽ có hiệu quả. player là mục tiêu giải quyết hiệu quả, sử dụng data:toCardEffect(). Hiện không có kỹ năng sử dụng timing này.
    PostCardEffected, --Sau khi lá bài đã giải quyết hiệu quả, player là mục tiêu giải quyết hiệu quả, sử dụng data:toCardEffect(). Timing này luôn xảy ra dùng lá bài có hiệu quả hay không. Hiện không có kỹ năng sử dụng timing này.
    CardFinished, --Sau khi kết toán xong lá bài. player là người sử dụng bài, sử dụng data:toCardUse().
    TrickCardCanceling, --Timing trước khi hỏi người chơi có vô giải khả kích hay không. player lần lượt là tất cả người chơi, sử dụng data:toCardEffect(). nếu on effect return true, người này không thể sử dụng vô giải khả kích. Quốc chiến chưa có tướng dùng, VT có SP giả hủ là ví dụ.
	
	
	GeneralShown, -- Ngay khi tướng được mở bởi minh trí. player là người mở tướng. sử dụng data:toBool(), true là chủ tướng, false là phó tướng. Thường dùng để đánh dấu ai sẽ được tiên phong hoặc lật khiến endgame do tất cả người chơi cùng phe.
    GeneralShowed, -- Sau khi mở tướng bởi minh trí, kích khi đang free. player là người mở tướng. sử dụng data:toStringList(). Nếu list có head thì vừa mở chủ tướng, có deputy thì vừa mở phó tướng
    GeneralHidden, -- Khi tướng bị úp. player là người úp tướng. sử dụng data:toBool(), true là chủ tướng, false là phó tướng. Thường dùng để vô hiệu các kỹ năng trạng thái như trâu thị.
    GeneralRemoved, -- Sau khi loại bỏ tướng. player là người loại bỏ tướng data:toString(). String có dạng {Mã tướng bị loại bỏ}:{kỹ năng 1}+{kỹ năng 2}... (không bao gồm {} )
	
	GeneralTransforming, -- Khi đổi phó tướng. player là người đổi, sử dụng data:toInt() để lấy số tướng được xem. Dùng ở Từ Thứ Phá Trận, đổi phó đc nhìn thêm 2 tướng.
	GeneralTransformed -- Sau khi đã đổi phó tướng. player là người đổi. không có data. Hiện không sử dụng.
	
	DFDebut, -- Khi 1 tướng được mở không phải do minh trí, ví dụ do đổi phó tướng, do bộc lộ dã tâm... player là người mở tướng. thường sử dụng cho những kỹ năng trạng thái như trâu thị, bật chế độ cấm lật tướng.
	
	CommandVerifying, -- Khi chấp hành quân lệnh. player là người chấp hành, sử dụng data.toString(). cấu trúc của string là {lí do}:{quân lệnh số}:{người phát quân lệnh}->{người thực hiện} (Không bao gồm {} ). Sử dụng với lý nghiên để chọn lại quân lệnh 
	
	
	
	--Những event hiếm dùng

    ChoiceMade, --Khi 1 lựa chọn bất kỳ được đưa ra. player là người đã lựa chọn, sử dụng data:toString(). Tin tôi đi, bạn không muốn sử dụng timing này đâu :)


	-- 2 cái này thì đừng hỏi, chúng nó là exception event. việc bạn dùng có thể khiến game xảy ra những lỗi trầm trọng
    StageChange, 
    TurnBroken, 
	-- 2 cái không bao h dùng
	
	FetchDrawPileCard, -- event đặc biệt khi người chơi thực hiện hành động rút chính xác 1 lá. có mục đích riêng, vui lòng không sử dụng
}
