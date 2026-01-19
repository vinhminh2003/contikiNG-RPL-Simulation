# Tìm hiểu về hệ điều hành Contiki NG dành cho WSNs
Contiki-NG là hệ điều hành nhúng mã nguồn mở dành cho:
- Wireless Sensor Networks (WSNs)
- IoT constrained devices (RAM vài KB, MCU yếu)
- Nghiên cứu IPv6, RPL, 6LoWPAN, CoAP

# RPL giải quyết bài toán gì ?
WSN có các đặc điểm: node có phần cứng hạn chế, liên kết không ổn định, năng lượng giới hạn.
RPL tạo ra DODAG (Destination Oriented Directed Acyclic Graph) là một loại đồ thị
mà các cạnh có hướng, không có chu trình lặp lại, và tất cả các đường đi đều hướng
về một điểm đích cụ thể. Loại đồ thị này thường được sử dụng trong các bài toán như 
lập lịch, phân tích luồng dữ liệu, hoặc các hệ thống mạng mà cần đảm bảo không có 
vòng lặp và có điểm kết thúc rõ ràng.
