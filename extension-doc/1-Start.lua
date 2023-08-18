-- QSanguosha DIY
-- Bài 1: Bắt đầu

-- Tôi là Lãng Khách
-- Bắt đầu từ file này, tôi sẽ hướng bạn đễ có thể làm cho mình 1 DIY
-- File này được viết dành cho phiên bản QSanguosha-LangKhach-QuocChien

-- Có thể không hoạt động ở những phiên bản khác của QSanguosha

-- DIY được viết bằng LUA script và lưu với đuôi .lua. Khuyến cáo sử dụng notepad++ để chỉnh sửa.
-- Tất cả dòng bắt đầu bằng -- sẽ được bỏ qua khi game đọc đến. Hay bạn nào làm dev rồi thì có thể hiểu đây là comment.


-- Để bắt đầu, chúng ta hãy tạo 1 pack mở rộng
-- Giống như các pack như Trận, Thế, Biến, Quyền... DIY cũng phải tôn tại trong pack.
extension = sgs.Package("LK_Diy_1", sgs.Package_GeneralPack, true)
-- extension là tên biến toàn cục, có thể truy cập, miễn là còn trong file này.
-- Lệnh sgs.Package là lệnh dùng để tạo 1 pack.
-- Tham số thứ nhất là 1 chuỗi ký tự, là tên mã của pack mở rộng.
--   Nó có thể là bất cứ tên gì bạn muốn. Trong QSGS, tên mã sử dụng tên tiếng Anh của pack. VD Formation là trận, Power là quyền.
-- Tham số thứ 2 là loại Pack mở rộng, chỉ sử dụng 2 tham số sau
--[[
sgs.Package_GeneralPack -- Pack tướng
sgs.Package_CardPack -- Pack bài đánh
]]
--   Pack tướng và bài đánh không cùng tồn tại trong 1 pack.
--   Trong hướng dẫn này, chúng ta sẽ thử làm 1 pack tướng cơ bản
-- Tham số thứ 3 mô tả việc Pack này có phải là DIY hay không. Nếu là DIY thì sẽ xuất hiện ở tab DIY của game.
--   Tham số này có thể không điền, lúc này được hiểu không phải DIY

-- Tiếp theo, chúng ta sẽ thử làm 1 tướng
-- Đạo Tặc - Quần Hùng - 2HP
-- 
daoze = sgs.General(extension, "daoze", "qun", 4, true) 
-- Lệnh này dùng để tạo ra 1 lá tướng
-- Tham số thứ nhất là pack mở rộng để biết tướng này thuộc pack nào.
--   Hãy truyền biến extension đã tạo bên trên
-- Tham số thứ 2 là tên mã của tướng này. Trong code sẽ tìm tướng này bằng tên đó. Thường tên mã sử dụng bính âm.
--   Tên hiển thị (Đạo Tặc) sẽ được tạo ở cuối file này.
-- Tham số thứ 3 là thế lực. Hiện tại game support những thế lực sau
--[[
qun: Quần Hùng
shu: Thục
wei: Ngụy
wu: Ngô
careerist: Dã Tâm
god: Nghe hay đấy, bạn nghĩ đó là Thần ư :))). Đúng, nhưng tướng này không thể chơi được. Tướng này sẽ chỉ xuất hiện trong wiki của game với mục đích credit.
]]
--   Nếu bạn muốn tướng này là tướng song quốc, sử dụng thêm lệnh sau
-- daoze:setSubordinateKingdom("wu")
-- Tham số thứ 4 là số máu. Thay vì 1.5, 2, 2.5 thì chúng ta hãy gấp đôi lên. VD như số 4 ở trên thì đây là tướng 2 máu.
-- Tham số thứ 5 là giới tính. true là nam, false là nữ.

-- Có tướng rồi thì đến kỹ năng thôi. Tôi sẽ thử làm 1 kỹ năng đơn giản.

-- Thần Thâu: Bạn có thể sử dụng lá Tép (♣) như Thuận Thủ Khiên Dương
shentou = sgs.CreateOneCardViewAsSkill{ 
--Với lệnh này, chúng ta có 1 năng có loại là OneCardViewAsSkill, hay có thể hiểu là sử dụng 1 lá như 1 cái gì đó.
--Không giống như ngoài đời bạn chơi, chỉ xem loại kỹ năng như kiểu tỏa định kỹ, hạn định kỹ thì trong code sẽ phải phân ra thành kỹ năng chuyển hóa, có thời điểm, kỹ năng trạng thái...
--VD này dùng để giải thích cách làm 1 kỹ năng chuyển hóa đơn giản. Các loại kỹ năng khác cũng như chi tiết từng dòng lệnh sẽ được đề cập ở hướng dẫn sau

	name = "shentou",
	-- Tên trong code của kỹ năng, giống tên tướng ở trên
	filter_pattern = ".|club|.|hand" ,
	-- Áp dụng cho kỹ năng chuyển hóa hoặc bỏ 1 lá để làm gì đó. Dòng trên có thể đọc là lá Tép trên tay.
	view_as = function(self, card)
		local new_card = sgs.Sanguosha:cloneCard("snatch", sgs.Card_SuitToBeDecided, -1)
		-- Lệnh này để tạo ra 1 lá Thuận thủ khiên dương ảo
		-- snatch là tên mã của thuận thủ khiên dương
		new_card:addSubcard(card:getId())
		-- id của là nguồn.
		new_card:setSkillName(self:objectName())
		-- để log cũng như kỹ năng khác biết thuận thủ này do kĩ năng nào tạo ra
		new_card:setShowSkill(self:objectName())
		-- cần có dòng này để lật tướng khi kích kỹ năng chuyển hóa
		return new_card
	end
	-- Cả cụm này để tạo ra 1 lá Thuận Thủ Khiên Dương chuyển hóa với lá gốc là lá tép trên tay.
}
shiqian:addSkill(shentou) 
--Lệnh này để cho đạo tặc có kỹ năng thần thâu

sgs.LoadTranslationTable{
	["LK_Diy_1"] = "Lãng Khách DIY 1" ,
	--Tên Pack
	
	["daoze"] = "Đạo Tặc",
	-- Tên tướng
	["#daoze"] = "Đạo tặc cũng cần xưng hào sao",
	-- Xưng hào sẽ thêm dấu # ở trước mã của tướng
	
	
	["shentou"] = "Thần Thâu",
	-- Tên kỹ năng
	[":shentou"] = "Bạn có thể sử dụng lá TÉP như Thuận Thủ Khiên Dương",
	-- Mô tả kỹ năng, thêm dấu : trước mã của kỹ năng

}
-- Đoạn trên giúp game có thể hiển thị thông tin tướng, kỹ năng.


-- Vậy là chúng ta tạo xong tướng đầu tiên, nhưng còn 1 bước cuối
-- return {extension} để cho game đọc được file này

return {extension}


-- Bạn có thể copy file này cho vào thư mục extension của game, đổi lại cái tên nào hay hay chút và bạn có thể chơi được tướng đạo tặc trong game.
-- Tuy nhiên nếu chỉ có thế, bạn sẽ không thấy ảnh tướng trong game. Để có hình ảnh, bạn hãy kiếm file ảnh với các kích thước phù hợp và cho vào các folder sau
-- \image\generals\card: Hiển thị card trong wiki và lúc chọn tướng
-- \fullskin\generals\full: Hiển thị tướng ở trong game.