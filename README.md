# Tìm hiểu về hệ điều hành Contiki NG dành cho WSNs
Contiki-NG là hệ điều hành nhúng mã nguồn mở dành cho:
- Wireless Sensor Networks (WSNs)
- IoT constrained devices (RAM vài KB, MCU yếu)
- Nghiên cứu IPv6, RPL, 6LoWPAN, CoAP

# RPL giải quyết bài toán gì ?
- WSN có các đặc điểm: node có phần cứng hạn chế, liên kết không ổn định, năng lượng giới hạn.
- RPL tạo ra DODAG (Destination Oriented Directed Acyclic Graph) là một loại đồ thị
mà các cạnh có hướng, không có chu trình lặp lại, và tất cả các đường đi đều hướng
về một điểm đích cụ thể. Loại đồ thị này thường được sử dụng trong các bài toán như 
lập lịch, phân tích luồng dữ liệu, hoặc các hệ thống mạng mà cần đảm bảo không có 
vòng lặp và có điểm kết thúc rõ ràng.

# Mô hình mô phỏng RPL với Contiki NG:
Yêu cầu: 
- Ubuntu 22.04: https://releases.ubuntu.com/jammy/.
- VMWare: https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion.
- Contiki NG: https://docs.contiki-ng.org/en/develop/.
- Cooja Simulation.

# Mô hình sẽ được mô phỏng với 1 node root (điểm đích) và nhiều node client sử dụng trực tiếp node cooja mote trên Cooja Simulation.
cd contiki-ng/tools/cooja
./gradlew run

add mote type -> cooja mote
- cooja mote (node root - green) -> rpl_root.c -> compile -> create.
- cooja mote (node client - yellow) -> rpl_client.c -> compile -> create.
<img width="401" height="401" alt="image" src="https://github.com/user-attachments/assets/b4553951-c128-4b60-8ce3-f77e220bba1b" />

# Kết quả mô phỏng:

<img width="628" height="567" alt="image" src="https://github.com/user-attachments/assets/07b6936c-820c-440a-9646-62d7e41febc0" />
<img width="626" height="567" alt="image" src="https://github.com/user-attachments/assets/09495c60-fe7d-4550-86ec-013692151750" />
<img width="627" height="564" alt="image" src="https://github.com/user-attachments/assets/e1b4712e-33a0-4831-9614-c9d05595c732" />


