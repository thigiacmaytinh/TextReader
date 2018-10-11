Chương trình sử dụng thư viện Tesseract để đọc text từ ảnh. Chương trình tự động tìm các ảnh chung folder với file exe để đọc text, sau đó in text ra cửa sổ Console.

Tesseract có training sẵn các bộ data cho các ngôn ngữ khác nhau ở: https://github.com/tesseract-ocr/tessdata

Chương trình sẽ load file data dựa vào file name trong config. Ví dụ: bạn sử dụng file vie.traineddata, thì trong file config bạn để là 
lang=vie

Liên hệ: https://www.facebook.com/vohungvi