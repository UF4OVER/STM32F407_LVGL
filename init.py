# -*- coding: utf-8 -*-
# -------------------------------

#  @Project : upper_computer
#  @Time    : 2024 - 12-20 18:12
#  @FileName: init.py
#  @Software: PyCharm 2024.1.6 (Professional Edition)
#  @System  : Windows 11 23H2
#  @Author  : 33974
#  @Contact : 
#  @Python  : 3.10

# -------------------------------



import os
import shutil
import sys


def main():
    try:
        # 先清除当前文件夹下的GUI和GUI_APP文件夹
        shutil.rmtree("GUI", ignore_errors=True)
        shutil.rmtree("GUI_APP", ignore_errors=True)
        # 在当前目录下创建GUI和GUI_APP文件夹
        os.makedirs("GUI_APP", exist_ok=True)
        # 在GUI文件夹下创建LVGL文件夹
        os.makedirs("GUI/src", exist_ok=True)
        os.makedirs("GUI/examples", exist_ok=True)
        # 将D:\lvgl\src文件夹复制到GUI/src文件夹中
        src_dir = r"D:\lvgl\src"
        dest_dir = r"GUI\src"
        for root, dirs, files in os.walk(src_dir):
            for file in files:
                src_path = os.path.join(root, file)
                dest_path = os.path.join(dest_dir, os.path.relpath(src_path, src_dir))
                os.makedirs(os.path.dirname(dest_path), exist_ok=True)
                shutil.copy2(src_path, dest_path)  # 使用copy2保留文件元数据
        # 复制D:\lvgl\lvgl.h 这个文件到GUI 这个位置
        src_path = r"D:\lvgl\lvgl.h"
        dest_path = r"GUI\lvgl.h"
        shutil.copy(src_path, dest_path)
        # 复制D:\lvgl\examples\porting中的文件到GUI/lvgl_port文件夹中，并且去掉文件名中的template
        src_dir = r"D:\lvgl\examples"
        dest_base_dir = r"GUI/examples"

        for root, dirs, files in os.walk(src_dir):
            for file in files:
                src_path = os.path.join(root, file)
                # 去掉文件名中的 "template"
                new_file_name = file.replace("_template", "")
                dest_path = os.path.join(dest_base_dir, os.path.relpath(src_path, src_dir).replace(file, new_file_name))
                # 确保目标目录存在
                os.makedirs(os.path.dirname(dest_path), exist_ok=True)
                # 复制文件
                shutil.copy2(src_path, dest_path)
        # 将 D:\lvgl\lv_conf_template.h 这个文件复制到 GUI/lv_conf.h 这个位置并重命名为lv_conf.h
        src_path = r"D:\lvgl\lv_conf_template.h"
        dest_path = r"GUI\lv_conf.h"
        shutil.copy(src_path, dest_path)

    except Exception as e:
        print(e)

def clear():
    shutil.rmtree("GUI", ignore_errors=True)
    shutil.rmtree("GUI_APP", ignore_errors=True)
    cmake(0)


def cmake(dir=1):
    # 检测当前目录下是否有CMakeLists.txt文件
    if os.path.exists("CMakeLists.txt"):
        try:
            # 打开CMakeLists.txt文件
            with open("CMakeLists.txt", "r") as f:
                content = f.read()

            # 替换其中的file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*")
            old_str = 'file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*")'
            new_str = 'file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*" "GUI/*.*")'
            if dir:
                modified_content = content.replace(old_str, new_str)
            else:
                modified_content = content.replace(new_str, old_str)

            # 如果内容有变化，则写回文件
            if modified_content != content:
                with open("CMakeLists.txt", "w") as f:
                    f.write(modified_content)
                print("CMakeLists.txt 文件已成功修改")
            else:
                print("CMakeLists.txt 文件无需修改")

        except Exception as e:
            print(f"修改 CMakeLists.txt 文件时出错: {e}")
    else:
        print("当前目录下没有 CMakeLists.txt 文件")
if __name__ == '__main__':
    # 接收参数，如果没有参数，则执行main函数
    if len(sys.argv) > 1:
        if sys.argv[1] == "clear":
            clear()
            print("清除成功")
        else:
            print("参数错误")
    elif len(sys.argv)>1 and sys.argv[1]=="make":
        main()
        cmake()
        print("复制成功")