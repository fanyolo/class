from PIL import Image
import numpy as np

def convert_image_to_rgb565_array(image_path, lcd_width, lcd_height):
    """
    将任意尺寸图片转成 RGB565 数组，供 TFT-LCD 显示
    """
    # 打开图片
    img = Image.open(image_path)

    # 缩放至 LCD 分辨率
    img = img.resize((lcd_width, lcd_height), Image.Resampling.LANCZOS)

    # 转换为 RGB 模式
    img = img.convert('RGB')

    # 获取像素数组 (H, W, 3)
    img_np = np.array(img)

    # 精确转换成 RGB565 (四舍五入法)
    r = ((img_np[:, :, 0].astype(np.uint16) * 31 + 127) // 255)  # 5 bit
    g = ((img_np[:, :, 1].astype(np.uint16) * 63 + 127) // 255)  # 6 bit
    b = ((img_np[:, :, 2].astype(np.uint16) * 31 + 127) // 255)  # 5 bit

    rgb565 = (r << 11) | (g << 5) | b

    # 转成一维数组
    rgb565_flat = rgb565.flatten().astype(np.uint16)

    return rgb565_flat

# 使用示例
if __name__ == "__main__":
    arr = convert_image_to_rgb565_array(r".jpg", 240,320)

    # 直接保存为 C 头文件
    c_filename = r"d:/Users/86187/Desktop/s32/test.h"
    array_name = "test"

    with open(c_filename, "w") as f:
        f.write(f"// Generated from image\n")
        f.write(f"const unsigned short {array_name}[{len(arr)}] = {{\n")

        for i, value in enumerate(arr):
            f.write(f"0x{value:04X}, ")
            if (i + 1) % 8 == 0:
                f.write("\n")

        f.write("\n};\n")

    print(f"转换完成，已保存为 {c_filename}")
