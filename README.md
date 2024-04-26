# Hero Battle
- Bài tập lớn môn học Lập trình nâng cao sử dụng ngôn ngữ C++ và thư viện SDL2
- Video giới thiệu game: <https://www.youtube.com/watch?v=EUNGyMjDoD0>
# Cách tải game
- Tải game được nén thành file zip ở trong link sau <https://github.com/thnh23/HeroBattle/releases/tag/v1.0.0>
- Giải nén vào thư mục rồi ấn vào file exe để chơi
# Giới thiệu game
- Trong Hero Battle, bạn sẽ điều khiển nhân vật hiệp sĩ đánh bại quái trong từng bản đồ. Sau khi đánh bại hết quái trong từng bản đồ, bạn di chuyển sang bản đồ tiếp theo. Nhiệm vụ của bạn là đánh bại boss để hoàn thành game. 
## 1.Cách chơi
- Khi bắt đầu vào game, bạn sẽ thấy môt màn hình chờ ![menu](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/menu.png)
+ Nút Play: bắt đầu game
+ Nút Infor: xem hướng dẫn di chuyển nhân vật
  + Phím A/D: nhân vật di chuyển trái, phải
  + Phím W: nhân vật nhảy
  + phím S: nhân vật phòng thủ
  + phím J: nhân vật tấn công
  + phím K: nhân vật sử dụng kĩ năng đặc biệt
+ Nút Close: kết thúc game
- Khi vào trong màn chơi:
+ Bạn sẽ thấy có các thanh chỉ số:
   + Máu: ![health_bar](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/healthPic.png) 
   + Năng lượng:![energy_bar](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/energyPic.png)
   + Tiền: ![coin](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/coinPic.png) 
+ Khi bạn đánh bại được quái vật sẽ rơi ra tiền. ![sample](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/sample.png)
+ Khi đã tích lũy được một số tiền nhất định, bạn có thể vào shop để mua các nâng cấp cho nhân vật
  ![shop](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/shopPic.png)
+ Khi muốn tạm dừng game, bạn ấn vào icon resume, đây là cửa sổ sẽ hiện ra
  ![resume](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/resumePic.png)
+ Khi đã đánh bại hết quái ở map, hãy đi sang phải để sang map tiếp theo
## 2.Điều kiện thắng và thua
- Chiến thắng: Khi bạn đánh bại thắng boss ở map cuối cùng ![gameWin](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/gameWin.png)
- Thất bại: Khi máu của nhân vật bằng 0!  ![gameLose](https://github.com/thnh23/HeroBattle/blob/master/HeroBattle/Image/gameOver.png)
# Mã nguồn tham khảo 
- Từ trang lazyfoo và youtuber Madsycode
# Đồ họa đã sử dụng
- Từ trang itch.io
# Soucre code game
+ Folder Animation: chứa class animation của game
+ Folder Camera: tạo background di chuyển cùng nhân vật
+ Folder Core: chứa tất cả các hoạt động, tính năng game
+ Folder Characters: xử lí các trạng thái, hoạt động của nhân vật, quái và boss
+ Folder GamePlay:
  + Chứa logic game
  + Gồm các game state: menu, resume,shop, win, lose
  + Chuyển map trong game 
+ Folder Graphic:
   + Render ảnh, ảnh mờ, chữ
   + Lưu trữ ảnh
   + Class Button: các nút chức năng của game 
   + Class HUD: biểu diễn các thông số nhân vật
+ Folder Inputs: xử lí các sự kiện của game: bàn phím và chuột
+ Folder Map: load map từ file .tmx
+ Folder Object: chứa base class của các vật thể trong game
+ Folder Physics: chứa các class xử lí va chạm, tọa độ nhân vật
+ Folder Timer: chứa class gọi thời gian trong game
+ Folder Vendor: thư viện để load file .tmx (nguồn youtuber Madsycode)
+ main.cpp: hàm main của chương trình, tối ưu độ mượt cho chương trình

