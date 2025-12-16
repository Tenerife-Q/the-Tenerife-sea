import tkinter as tk
from tkinter import messagebox, ttk
import random


class HashTableVisualizer:
    def __init__(self, root):
        self.root = root
        self.root.title("哈希表可视化工具 - 三种冲突解决方法演示 V2")
        self.root.geometry("1200x800")
        self.root.resizable(True, True)

        # 哈希表参数
        self.table_size = 10  # 表大小
        self.probing_method = "linear"  # 默认线性探测
        self.hash_method = "division"  # 默认哈希函数
        self.open_table = [None] * self.table_size  # 开放式探测表
        self.chain_table = [[] for _ in range(self.table_size)]  # 链地址法表

        # 统计信息
        self.total_probes = 0  # 总探测次数
        self.total_elements = 0  # 总元素数
        self.last_operation = ""  # 最后操作
        self.conflict_info = []  # 冲突信息
        self.highlighted_cells = []  # 高亮的单元格
        self.operation_feedback_label = None  # 用于显示醒目操作反馈的标签

        # 创建界面
        self.create_widgets()
        self.draw_table()

    def create_widgets(self):
        # 主框架
        main_frame = tk.Frame(self.root)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        # 左侧控制面板
        left_frame = tk.Frame(main_frame, width=300)
        left_frame.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 10))
        left_frame.pack_propagate(False)

        # 哈希函数选择
        hash_func_frame = tk.LabelFrame(left_frame, text="哈希函数", font=("Arial", 12, "bold"))
        hash_func_frame.pack(fill=tk.X, pady=(0, 10))

        self.hash_method_var = tk.StringVar(value="division")
        hash_methods = [
            ("除留余数法", "division", "h(k) = k % table_size"),
            ("平方取中法", "midsquare", "h(k) = (k² 中间几位) % table_size")
        ]

        for text, value, desc in hash_methods:
            frame = tk.Frame(hash_func_frame)
            frame.pack(fill=tk.X, padx=5, pady=2)
            tk.Radiobutton(frame, text=text, variable=self.hash_method_var,
                          value=value, command=lambda v=value: self.set_hash_method(v),
                          font=("Arial", 10)).pack(anchor=tk.W)
            tk.Label(frame, text=desc, font=("Arial", 8), fg="gray").pack(anchor=tk.W, padx=20)

        # 方法选择框
        method_frame = tk.LabelFrame(left_frame, text="冲突解决方法", font=("Arial", 12, "bold"))
        method_frame.pack(fill=tk.X, pady=(0, 10))

        self.method_var = tk.StringVar(value="linear")
        methods = [
            ("线性探测", "linear", "探测序列: h(k), h(k)+1, h(k)+2, ..."),
            ("二次探测", "quadratic", "探测序列: h(k) ± 1², h(k) ± 2², ..."),
            ("链地址法", "chain", "相同哈希值形成链表 (无序)")
        ]

        for text, value, desc in methods:
            frame = tk.Frame(method_frame)
            frame.pack(fill=tk.X, padx=5, pady=2)
            tk.Radiobutton(frame, text=text, variable=self.method_var,
                          value=value, command=lambda v=value: self.set_method(v),
                          font=("Arial", 10, "bold")).pack(anchor=tk.W)
            tk.Label(frame, text=desc, font=("Arial", 8), fg="gray").pack(anchor=tk.W, padx=20)

        # 操作面板
        op_frame = tk.LabelFrame(left_frame, text="数据操作", font=("Arial", 12, "bold"))
        op_frame.pack(fill=tk.X, pady=(0, 10))

        # 表大小设置
        size_frame = tk.Frame(op_frame)
        size_frame.pack(fill=tk.X, padx=5, pady=5)
        tk.Label(size_frame, text="表大小:", font=("Arial", 10)).pack(side=tk.LEFT)
        self.size_var = tk.StringVar(value=str(self.table_size))
        size_spinbox = tk.Spinbox(size_frame, from_=5, to=20, width=5, textvariable=self.size_var,
                                  font=("Arial", 10), command=self.change_table_size)
        size_spinbox.pack(side=tk.LEFT, padx=5)
        tk.Button(size_frame, text="应用", command=self.change_table_size,
                  bg="lightblue", font=("Arial", 8)).pack(side=tk.LEFT, padx=2)

        # 输入框
        input_frame = tk.Frame(op_frame)
        input_frame.pack(fill=tk.X, padx=5, pady=5)
        tk.Label(input_frame, text="数据值:", font=("Arial", 10)).pack(side=tk.LEFT)
        self.value_entry = tk.Entry(input_frame, width=15, font=("Arial", 12))
        self.value_entry.pack(side=tk.LEFT, padx=5)
        self.value_entry.bind('<Return>', lambda e: self.insert())

        # 哈希计算显示
        self.hash_calc_var = tk.StringVar(value="输入数值查看哈希计算")
        hash_label = tk.Label(op_frame, textvariable=self.hash_calc_var,
                              font=("Arial", 9), fg="darkgreen", wraplength=280)
        hash_label.pack(fill=tk.X, padx=5, pady=2)

        # 操作按钮
        btn_frame = tk.Frame(op_frame)
        btn_frame.pack(fill=tk.X, padx=5, pady=5)

        buttons = [
            ("插入", self.insert, "lightgreen"),
            ("查找", self.search, "lightblue"),
            ("删除", self.delete, "lightcoral"),
            ("重置", self.reset, "lightgray")
        ]

        for text, command, color in buttons:
            btn = tk.Button(btn_frame, text=text, command=command,
                           bg=color, font=("Arial", 10, "bold"), width=8)
            btn.pack(side=tk.LEFT, padx=2)

        # 快速测试
        test_frame = tk.LabelFrame(left_frame, text="快速测试", font=("Arial", 12, "bold"))
        test_frame.pack(fill=tk.X, pady=(0, 10))

        tk.Button(test_frame, text="随机插入5个数", command=self.random_insert,
                  bg="yellow", font=("Arial", 10)).pack(fill=tk.X, padx=5, pady=2)
        tk.Button(test_frame, text="冲突测试序列", command=self.conflict_test,
                  bg="orange", font=("Arial", 10)).pack(fill=tk.X, padx=5, pady=2)

        # 统计信息面板
        stats_frame = tk.LabelFrame(left_frame, text="性能统计", font=("Arial", 12, "bold"))
        stats_frame.pack(fill=tk.X, pady=(0, 10))

        self.stats_text = tk.Text(stats_frame, height=8, width=35, font=("Arial", 9))
        self.stats_text.pack(padx=5, pady=5)

        # 状态显示
        self.status_var = tk.StringVar(value="就绪 - 选择冲突解决方法开始测试")
        status_label = tk.Label(left_frame, textvariable=self.status_var,
                                font=("Arial", 10), fg="blue", wraplength=280, justify=tk.LEFT)
        status_label.pack(fill=tk.X, pady=5)

        # 右侧画布
        canvas_frame = tk.Frame(main_frame)
        canvas_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

        self.canvas = tk.Canvas(canvas_frame, bg="white", highlightthickness=1, relief=tk.SUNKEN)
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # 绑定输入框变化事件
        self.value_entry.bind('<KeyRelease>', self.update_hash_calculation)

    def change_table_size(self):
        """改变表大小"""
        try:
            new_size = int(self.size_var.get())
            if new_size < 5 or new_size > 20:
                messagebox.showerror("错误", "表大小必须在5-20之间！")
                self.size_var.set(str(self.table_size))
                return

            if new_size != self.table_size:
                self.table_size = new_size
                self.reset()
        except ValueError:
            self.size_var.set(str(self.table_size))

    def update_hash_calculation(self, event=None):
        """更新哈希计算显示"""
        try:
            value = self.value_entry.get().strip()
            if value:
                num_value = int(value)
                hash_result = self.hash_function(num_value)

                if self.hash_method == "division":
                    self.hash_calc_var.set(f"除留余数法: {num_value} % {self.table_size} = {hash_result}")
                else:  # midsquare
                    squared = num_value * num_value
                    self.hash_calc_var.set(f"平方取中法: {num_value}² = {squared} → ... → {hash_result}")
            else:
                self.hash_calc_var.set("输入数值查看哈希计算")
        except ValueError:
            self.hash_calc_var.set("请输入有效整数")

    def set_hash_method(self, method):
        """设置哈希函数"""
        if self.hash_method != method:
            self.hash_method = method
            self.reset()
            self.update_hash_calculation()  # 更新显示

    def set_method(self, method):
        if self.probing_method != method:
            self.probing_method = method
            self.reset()
            self.update_method_info()

    def update_method_info(self):
        """更新方法说明信息"""
        method_info = {
            "linear": "线性探测：逐个检查下一个位置\n优点：实现简单\n缺点：容易产生聚集",
            "quadratic": "二次探测：按平方数跳跃探测\n优点：减少聚集现象\n缺点：可能无法探测所有位置",
            "chain": "链地址法：相同哈希值形成链表\n优点：不会产生聚集\n缺点：需要额外空间"
        }
        info = method_info.get(self.probing_method, "")
        self.status_var.set(f"当前方法：{info}")

    def calculate_asl(self):
        """计算平均查找长度"""
        if self.total_elements == 0:
            return 0
        return self.total_probes / self.total_elements

    def update_stats(self):
        """更新统计信息"""
        asl = self.calculate_asl()
        load_factor = self.total_elements / self.table_size

        stats_text = f"""=== 哈希表统计信息 ===
方法: {self.get_method_name()}
表大小: {self.table_size}
已存元素: {self.total_elements}
装载因子: {load_factor:.2f}
平均查找长度(ASL): {asl:.2f}
总探测次数: {self.total_probes}

=== 最近操作 ===
{self.last_operation}

=== 冲突信息 ===
"""

        for info in self.conflict_info[-5:]:  # 显示最近5次冲突
            stats_text += f"{info}\n"

        # 理论ASL比较
        if self.probing_method in ["linear", "quadratic"]:
            theoretical_asl = 1 + load_factor / 2
            stats_text += f"\n理论ASL: {theoretical_asl:.2f}"

        self.stats_text.delete(1.0, tk.END)
        self.stats_text.insert(1.0, stats_text)

    def get_method_name(self):
        names = {"linear": "线性探测", "quadratic": "二次探测", "chain": "链地址法"}
        return names.get(self.probing_method, "未知")

    def random_insert(self):
        """随机插入测试"""
        values = random.sample(range(1, 100), 5)
        for value in values:
            self.value_entry.delete(0, tk.END)
            self.value_entry.insert(0, str(value))
            self.insert()
            self.root.update()
            self.root.after(500)  # 延迟500ms

    def conflict_test(self):
        """冲突测试序列"""
        # 设计会产生冲突的数据
        if self.probing_method == "chain":
            test_values = [10, 20, 30]  # 都映射到位置0
        else:
            test_values = [10, 20, 30, 40]  # 产生连续冲突

        for value in test_values:
            self.value_entry.delete(0, tk.END)
            self.value_entry.insert(0, str(value))
            self.insert()
            self.root.update()
            self.root.after(800)  # 延迟800ms

    def hash_function_midsquare(self, value):
        """平方取中法哈希函数"""
        squared = value * value
        str_squared = str(squared)

        # 确定要提取的位数，与表大小的位数相关
        num_digits_table = len(str(self.table_size - 1))

        # 如果平方后的位数小于要提取的位数，直接用
        if len(str_squared) <= num_digits_table:
            return int(str_squared) % self.table_size

        # 找到中间位置
        mid_index = len(str_squared) // 2
        start_index = mid_index - (num_digits_table // 2)

        # 提取中间的几位数
        extracted_str = str_squared[start_index: start_index + num_digits_table]

        return int(extracted_str) % self.table_size

    def hash_function(self, value):
        """根据选择的哈希方法计算哈希值"""
        val = int(value)
        if self.hash_method == "midsquare":
            return self.hash_function_midsquare(val)
        else:  # division
            return val % self.table_size

    def open_probing_insert(self, value):
        """开放式探测插入（线性或二次）"""
        index = self.hash_function(value)
        original_index = index
        probe_sequence = [index]

        # 显示哈希计算过程
        if self.hash_method == "division":
            hash_calc = f"h({value}) = {value} % {self.table_size} = {index}"
        else:
            hash_calc = f"h({value}) = (sqr mid) % {self.table_size} = {index}"

        for i in range(self.table_size):
            if self.probing_method == 'linear':
                current_index = (index + i) % self.table_size
                probe_calc = f"h({value}) + {i} = {index} + {i} = {current_index}" if i > 0 else ""
            else:  # quadratic with ±i²
                if i == 0:
                    current_index = index
                    probe_calc = ""
                else:
                    # 探测序列: +1^2, -1^2, +2^2, -2^2, ...
                    step = (i + 1) // 2
                    sign = 1 if i % 2 != 0 else -1
                    offset = sign * (step * step)
                    current_index = (index + offset) % self.table_size
                    op = "+" if sign > 0 else "-"
                    probe_calc = f"h({value}) {op} {step}² = {index} {op} {step * step} = {current_index}"

            if i > 0:  # 记录探测序列
                probe_sequence.append(current_index)

            if self.open_table[current_index] is None or self.open_table[current_index] == "deleted":
                self.open_table[current_index] = value
                self.total_probes += (i + 1)
                self.total_elements += 1

                # 记录冲突信息
                if i > 0:
                    conflict_msg = f"插入{value}: {hash_calc} → 冲突 → {probe_calc} → 位置{current_index}"
                    self.conflict_info.append(conflict_msg)
                else:
                    conflict_msg = f"插入{value}: {hash_calc} → 直接存储"

                self.last_operation = conflict_msg
                self.highlighted_cells = probe_sequence
                return True, i, probe_sequence

        return False, self.table_size, probe_sequence

    def chain_insert(self, value):
        """链地址法插入（无序插入，后插到末尾）"""
        index = self.hash_function(value)
        if self.hash_method == "division":
            hash_calc = f"h({value}) = {value} % {self.table_size} = {index}"
        else:
            hash_calc = f"h({value}) = (sqr mid) % {self.table_size} = {index}"

        if value not in self.chain_table[index]:
            # 无序插入：直接追加到链表末尾
            self.chain_table[index].append(value)

            self.total_elements += 1
            self.total_probes += len(self.chain_table[index])  # 链表长度即为查找次数

            if len(self.chain_table[index]) > 1:
                conflict_msg = f"插入{value}: {hash_calc} → 冲突 → 追加到链表末尾"
                self.conflict_info.append(conflict_msg)
            else:
                conflict_msg = f"插入{value}: {hash_calc} → 直接添加"

            self.last_operation = conflict_msg
            self.highlighted_cells = [index]
            return True, 0
        return False, 0

    def insert(self):
        """插入数据"""
        try:
            value = int(self.value_entry.get().strip())
        except ValueError:
            messagebox.showerror("错误", "请输入有效的整数！")
            return

        self.value_entry.delete(0, tk.END)

        if self.probing_method in ["linear", "quadratic"]:
            success, steps, probe_sequence = self.open_probing_insert(value)
            if success:
                self.status_var.set(f"✅ 插入成功！值: {value}, 探测步数: {steps + 1}")
                self.show_operation_feedback(f"插入: {value}\n位置: {probe_sequence[-1]}\n探测: {steps + 1}次", "green")
            else:
                self.status_var.set("❌ 插入失败：哈希表已满！")
        else:
            success, _ = self.chain_insert(value)
            if success:
                self.status_var.set(f"✅ 插入成功！值: {value}, 哈希位置: {self.hash_function(value)}")
                self.show_operation_feedback(f"插入: {value}\n位置: {self.hash_function(value)}", "green")
            else:
                self.status_var.set("❌ 插入失败：值已存在！")

        self.update_stats()
        self.draw_table()

    def open_probing_search(self, value):
        """开放式探测查找（线性或二次）"""
        index = self.hash_function(value)
        probe_sequence = [index]
        if self.hash_method == "division":
            hash_calc = f"h({value}) = {value} % {self.table_size} = {index}"
        else:
            hash_calc = f"h({value}) = (sqr mid) % {self.table_size} = {index}"

        for i in range(self.table_size):
            if self.probing_method == 'linear':
                current_index = (index + i) % self.table_size
                probe_calc = f"h({value}) + {i} = {index} + {i} = {current_index}" if i > 0 else ""
            else:  # quadratic with ±i²
                if i == 0:
                    current_index = index
                    probe_calc = ""
                else:
                    step = (i + 1) // 2
                    sign = 1 if i % 2 != 0 else -1
                    offset = sign * (step * step)
                    current_index = (index + offset) % self.table_size
                    op = "+" if sign > 0 else "-"
                    probe_calc = f"h({value}) {op} {step}² = {index} {op} {step * step} = {current_index}"

            if i > 0:
                probe_sequence.append(current_index)

            if self.open_table[current_index] is None:
                if i > 0:
                    search_msg = f"查找{value}: {hash_calc} → 冲突 → {probe_calc} → 空槽，查找失败"
                else:
                    search_msg = f"查找{value}: {hash_calc} → 空槽，查找失败"
                self.last_operation = search_msg
                return False, -1, i, probe_sequence  # 遇到空槽，查找失败

            if self.open_table[current_index] == value:
                if i > 0:
                    search_msg = f"查找{value}: {hash_calc} → 冲突 → {probe_calc} → 找到"
                else:
                    search_msg = f"查找{value}: {hash_calc} → 直接找到"
                self.last_operation = search_msg
                return True, current_index, i, probe_sequence

        return False, -1, self.table_size, probe_sequence

    def chain_search(self, value):
        """链地址法查找"""
        index = self.hash_function(value)
        for i, v in enumerate(self.chain_table[index]):
            if v == value:
                return True, index, i
        return False, -1, -1

    def search(self):
        """查找数据"""
        try:
            value = int(self.value_entry.get().strip())
        except ValueError:
            messagebox.showerror("错误", "请输入有效的整数！")
            return

        self.value_entry.delete(0, tk.END)

        if self.probing_method in ["linear", "quadratic"]:
            found, index, steps, probe_sequence = self.open_probing_search(value)
            if found:
                self.status_var.set(f"🔍 查找成功！值: {value}, 位置: {index}, 探测步数: {steps + 1}")
                self.highlighted_cells = probe_sequence
                self.show_operation_feedback(f"找到: {value}\n位置: {index}\n探测: {steps + 1}次", "blue")
            else:
                self.status_var.set(f"❌ 查找失败：值 {value} 不存在！探测了{steps}次")
                self.highlighted_cells = probe_sequence
                self.show_operation_feedback(f"未找到: {value}\n探测: {steps}次", "red")
        else:
            index = self.hash_function(value)
            if self.hash_method == "division":
                hash_calc = f"h({value}) = {value} % {self.table_size} = {index}"
            else:
                hash_calc = f"h({value}) = (sqr mid) % {self.table_size} = {index}"

            found, _, pos = self.chain_search(value)
            if found:
                self.status_var.set(f"🔍 查找成功！值: {value}, 哈希位置: {index}, 链表位置: {pos + 1}")
                self.highlighted_cells = [index]
                self.last_operation = f"查找{value}: {hash_calc} → 链表第{pos + 1}个位置找到"
                self.show_operation_feedback(f"找到: {value}\n位置: {index}\n链表第 {pos + 1} 个", "blue")
            else:
                self.status_var.set(f"❌ 查找失败：值 {value} 不存在！")
                self.highlighted_cells = [self.hash_function(value)]
                self.last_operation = f"查找{value}: {hash_calc} → 链表中未找到"
                self.show_operation_feedback(f"未找到: {value}", "red")

        self.update_stats()
        self.draw_table()

    def open_probing_delete(self, value):
        """开放式探测删除（标记删除）"""
        found, index, _, _ = self.open_probing_search(value)
        if found:
            self.open_table[index] = "deleted"  # 标记为已删除
            return True
        return False

    def chain_delete(self, value):
        """链地址法删除"""
        index = self.hash_function(value)
        if value in self.chain_table[index]:
            self.chain_table[index].remove(value)
            return True
        return False

    def delete(self):
        """删除数据"""
        try:
            value = int(self.value_entry.get().strip())
        except ValueError:
            messagebox.showerror("错误", "请输入有效的整数！")
            return

        self.value_entry.delete(0, tk.END)

        if self.probing_method in ["linear", "quadratic"]:
            success = self.open_probing_delete(value)
            if success:
                self.total_elements -= 1
                self.status_var.set(f"🗑️ 删除成功！值: {value} (标记删除)")
                self.last_operation = f"删除{value}: 成功，标记为已删除"
            else:
                self.status_var.set(f"❌ 删除失败：值 {value} 不存在！")
                self.last_operation = f"删除{value}: 失败，元素不存在"
        else:
            success = self.chain_delete(value)
            if success:
                self.total_elements -= 1
                self.status_var.set(f"🗑️ 删除成功！值: {value}")
                self.last_operation = f"删除{value}: 成功，从链表中移除"
            else:
                self.status_var.set(f"❌ 删除失败：值 {value} 不存在！")
                self.last_operation = f"删除{value}: 失败，元素不存在"

        self.highlighted_cells = []
        self.update_stats()
        self.draw_table()

    def reset(self):
        """重置哈希表"""
        self.open_table = [None] * self.table_size
        self.chain_table = [[] for _ in range(self.table_size)]
        self.total_probes = 0
        self.total_elements = 0
        self.conflict_info = []
        self.highlighted_cells = []
        self.last_operation = "哈希表已重置"
        self.status_var.set("🔄 哈希表已重置")
        self.update_stats()
        self.draw_table()

    def show_operation_feedback(self, text, color):
        """显示一个醒目的、会自动消失的操作反馈标签"""
        if self.operation_feedback_label:
            self.operation_feedback_label.destroy()

        self.operation_feedback_label = tk.Label(self.canvas, text=text, font=("Arial", 18, "bold"),
                                                 bg="white", fg=color, relief=tk.RAISED, borderwidth=2)

        # 确保canvas已更新以获取尺寸
        self.canvas.update_idletasks()
        canvas_width = self.canvas.winfo_width()
        canvas_height = self.canvas.winfo_height()

        # 放置在画布中心
        self.operation_feedback_label.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

        # 1.5秒后自动销毁
        self.root.after(1500, lambda: self.operation_feedback_label.destroy() if self.operation_feedback_label else None)

    def draw_table(self):
        """绘制哈希表可视化界面"""
        self.canvas.delete("all")  # 清空画布

        width = self.canvas.winfo_width()
        height = self.canvas.winfo_height()

        # 确保canvas已经完全初始化
        if width <= 1 or height <= 1:
            self.root.after(100, self.draw_table)
            return

        if self.probing_method in ["linear", "quadratic"]:
            self.draw_open_addressing(width, height)
        else:
            self.draw_chaining(width, height)

        # 绘制说明文字
        self.canvas.create_text(width // 2, height - 30,
                                text="💡 操作说明：输入数值后点击按钮进行插入/查找/删除，观察冲突解决过程",
                                font=("Arial", 10), fill="gray")

    def draw_open_addressing(self, width, height):
        """绘制开放寻址法（自适应大小）"""
        title = f"开放寻址哈希表 - {self.get_method_name()}"

        # 动态计算单元格大小
        available_width = width - 100  # 预留边距

        if self.table_size <= 8:
            cell_width = min(100, available_width // self.table_size - 15)
        elif self.table_size <= 12:
            cell_width = min(80, available_width // self.table_size - 12)
        else:
            cell_width = min(70, available_width // self.table_size - 10)

        cell_height = 80

        # 确保最小可用大小
        cell_width = max(50, cell_width)

        x_start = (width - self.table_size * (cell_width + 10)) // 2

        # 确保x_start不为负数
        if x_start < 10:
            x_start = 10
            cell_width = max(45, (available_width - 20) // self.table_size - 10)

        y_center = height // 2

        for i in range(self.table_size):
            x = x_start + i * (cell_width + 10)
            y = y_center - cell_height // 2

            # 确定颜色
            if i in self.highlighted_cells:
                if self.open_table[i] is not None and self.open_table[i] != "deleted":
                    color = "gold"  # 高亮已占用
                else:
                    color = "lightyellow"  # 高亮空位置
                outline_color = "red"
                outline_width = 3
            else:
                if self.open_table[i] is None:
                    color = "white"
                elif self.open_table[i] == "deleted":
                    color = "lightgray"
                else:
                    color = "lightblue"
                outline_color = "gray"
                outline_width = 1

            # 绘制方框
            self.canvas.create_rectangle(x, y, x + cell_width, y + cell_height,
                                         outline=outline_color, fill=color, width=outline_width)

            # 动态调整字体大小
            font_size = min(14, cell_width // 6)
            index_font_size = min(10, cell_width // 8)

            # 绘制内容
            if self.open_table[i] is None:
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 - 8,
                                        text="空", font=("Arial", font_size), fill="gray")
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 + 8,
                                        text=f"[{i}]", font=("Arial", index_font_size), fill="gray")
            elif self.open_table[i] == "deleted":
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 - 8,
                                        text="已删除", font=("Arial", min(font_size, 10)), fill="red")
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 + 8,
                                        text=f"[{i}]", font=("Arial", index_font_size))
            else:
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 - 8,
                                        text=str(self.open_table[i]), font=("Arial", font_size, "bold"))
                self.canvas.create_text(x + cell_width // 2, y + cell_height // 2 + 8,
                                        text=f"[{i}]", font=("Arial", index_font_size))
                # 显示哈希值
                hash_val = self.hash_function(self.open_table[i])
                if hash_val != i and cell_width > 60:  # 只有足够宽度时才显示
                    self.canvas.create_text(x + cell_width // 2, y - 15,
                                            text=f"h({self.open_table[i]})={hash_val}",
                                            font=("Arial", min(8, cell_width // 10)), fill="blue")

        # 绘制标题
        self.canvas.create_text(width // 2, 50, text=title, font=("Arial", 16, "bold"))

        # 绘制哈希函数说明
        if self.hash_method == "division":
            formula_text = f"哈希函数: h(k) = k % {self.table_size}"
        else:
            formula_text = f"哈希函数: 平方取中法后对 {self.table_size} 取模"
        self.canvas.create_text(width // 2, 75, text=formula_text,
                                font=("Arial", 12), fill="darkblue")

        # 绘制探测序列箭头
        if len(self.highlighted_cells) > 1:
            self.draw_probe_arrows(x_start, y_center, cell_width, cell_height)

        # 如果表格过宽，显示提示
        total_width = self.table_size * (cell_width + 10)
        if total_width > width - 50:
            self.canvas.create_text(width // 2, height - 15,
                                    text="⚠️ 表格过宽，建议减小表大小或扩大窗口",
                                    font=("Arial", 10), fill="red")

    def draw_chaining(self, width, height):
        """绘制链地址法（竖式链表，无序）"""
        title = "链地址法哈希表 - 竖式链表（无序）"

        # 计算最大链表长度，确定合适的单元格大小
        max_chain_length = max([len(chain) for chain in self.chain_table]) if any(self.chain_table) else 0
        available_width = width - 100  # 预留边距
        available_height = height - 200  # 预留标题和说明空间

        # 动态调整单元格大小
        if self.table_size <= 8:
            cell_width = min(100, available_width // self.table_size - 15)
        elif self.table_size <= 12:
            cell_width = min(80, available_width // self.table_size - 12)
        else:
            cell_width = min(70, available_width // self.table_size - 10)

        cell_height = 35

        # 如果链表过长，调整单元格高度
        if max_chain_length > 5:
            cell_height = max(30, min(cell_height, available_height // (max_chain_length + 3)))

        x_start = (width - self.table_size * (cell_width + 12)) // 2

        # 确保x_start不为负数
        if x_start < 10:
            x_start = 10
            cell_width = max(50, (available_width - 20) // self.table_size - 12)

        for i in range(self.table_size):
            x = x_start + i * (cell_width + 12)
            y = 120  # 表头位置

            # 高亮当前操作的位置
            highlight = i in self.highlighted_cells
            header_color = "lightyellow" if highlight else "lightblue"
            header_outline = "red" if highlight else "blue"

            # 绘制表头方框
            self.canvas.create_rectangle(x, y, x + cell_width, y + cell_height,
                                         outline=header_outline, fill=header_color,
                                         width=3 if highlight else 2)
            self.canvas.create_text(x + cell_width // 2, y + cell_height // 2,
                                    text=f"[{i}]", font=("Arial", min(12, cell_width // 8), "bold"))

            # 绘制竖式链表节点（无序，按插入顺序）
            chain_length = len(self.chain_table[i])
            node_y = y + cell_height + 8

            if chain_length == 0:
                # 显示NULL指针
                self.canvas.create_line(x + cell_width // 2, y + cell_height,
                                        x + cell_width // 2, node_y + 12, width=2, fill="gray")
                self.canvas.create_text(x + cell_width // 2, node_y + 20,
                                        text="NULL", font=("Arial", min(10, cell_width // 10)), fill="gray")
            else:
                # 绘制指向第一个节点的箭头
                self.canvas.create_line(x + cell_width // 2, y + cell_height,
                                        x + cell_width // 2, node_y,
                                        arrow=tk.LAST, width=2, fill="blue")

                # 直接使用存储的链表，不再排序（无序）
                chain = self.chain_table[i]

                # 绘制链表节点（竖向排列）
                for j, value in enumerate(chain):
                    # 计算节点位置
                    current_y = node_y + j * (cell_height + 8)

                    # 检查是否超出可视区域
                    if current_y + cell_height > height - 60:
                        # 如果超出，显示省略号
                        self.canvas.create_text(x + cell_width // 2, current_y,
                                                text="...", font=("Arial", 12), fill="red")
                        break

                    # 节点方框
                    node_color = "lightgreen" if not highlight else "gold"
                    self.canvas.create_rectangle(x, current_y, x + cell_width, current_y + cell_height,
                                                 outline="green", fill=node_color, width=2)

                    # 节点值
                    font_size = min(12, cell_width // 7)
                    self.canvas.create_text(x + cell_width // 2, current_y + cell_height // 2,
                                            text=str(value), font=("Arial", font_size, "bold"))

                    # 显示节点序号（按插入顺序）
                    if cell_width > 60:  # 只有足够宽度时才显示序号
                        self.canvas.create_text(x - 15, current_y + cell_height // 2,
                                                text=f"{j + 1}", font=("Arial", min(10, cell_width // 10)),
                                                fill="blue")

                    # 绘制指向下一个节点的箭头（除最后一个节点）
                    if j < len(chain) - 1:
                        next_y = current_y + cell_height
                        self.canvas.create_line(x + cell_width // 2, next_y,
                                                x + cell_width // 2, next_y + 8,
                                                arrow=tk.LAST, width=1, fill="green")
                    else:
                        # 最后一个节点指向NULL
                        next_y = current_y + cell_height
                        self.canvas.create_line(x + cell_width // 2, next_y,
                                                x + cell_width // 2, next_y + 8, width=1, fill="gray")
                        self.canvas.create_line(x + cell_width // 2 - 5, next_y + 8,
                                                x + cell_width // 2 + 5, next_y + 8, width=1, fill="gray")

                # 显示链表长度信息
                self.canvas.create_text(x + cell_width // 2, y - 12,
                                        text=f"长度:{chain_length}",
                                        font=("Arial", min(8, cell_width // 10)), fill="blue")

        # 绘制标题
        self.canvas.create_text(width // 2, 40, text=title, font=("Arial", 16, "bold"))

        # 绘制哈希函数说明
        if self.hash_method == "division":
            formula_text = f"哈希函数: h(k) = k % {self.table_size}"
        else:
            formula_text = f"哈希函数: 平方取中法后对 {self.table_size} 取模"
        self.canvas.create_text(width // 2, 65, text=formula_text,
                                font=("Arial", 12), fill="darkblue")

        # 如果有表格被截断，显示提示
        if max_chain_length > 0:
            max_visible_nodes = (height - 200) // (cell_height + 8)
            if max_chain_length > max_visible_nodes:
                self.canvas.create_text(width // 2, height - 15,
                                        text="⚠️ 部分链表过长未完全显示，请扩大窗口或重置",
                                        font=("Arial", 10), fill="red")

    def draw_probe_arrows(self, x_start, y_center, cell_width, cell_height):
        """绘制探测序列箭头（优化防重叠）"""

        for i in range(len(self.highlighted_cells) - 1):
            current_pos_idx = self.highlighted_cells[i]
            next_pos_idx = self.highlighted_cells[i + 1]

            # 计算起点和终点坐标
            x_start_arrow = x_start + current_pos_idx * (cell_width + 10) + cell_width // 2
            x_end_arrow = x_start + next_pos_idx * (cell_width + 10) + cell_width // 2

            # 动态调整箭头高度，避免重叠
            # 奇数次探测在下方，偶数次在上方，并逐渐远离
            arrow_level = (i // 2) + 1
            y_offset = (25 + arrow_level * 10) * (1 if i % 2 == 0 else -1)
            y_arrow = y_center + y_offset

            # 绘制水平线
            self.canvas.create_line(x_start_arrow, y_arrow, x_end_arrow, y_arrow,
                                    arrow=tk.LAST, width=2, fill="red", dash=(4, 2))

            # 绘制从单元格到水平线的垂直线
            self.canvas.create_line(x_start_arrow, y_center + cell_height // 2, x_start_arrow, y_arrow,
                                    width=1, fill="red", dash=(4, 2))
            self.canvas.create_line(x_end_arrow, y_center + cell_height // 2, x_end_arrow, y_arrow,
                                    width=1, fill="red", dash=(4, 2))

            # 在箭头上标记探测步数
            self.canvas.create_text((x_start_arrow + x_end_arrow) / 2, y_arrow - 10,
                                    text=f"第{i + 1}次探测", font=("Arial", 8), fill="black")


# 运行程序
if __name__ == "__main__":
    root = tk.Tk()

    # 设置程序图标和样式
    try:
        root.iconbitmap('hash_icon.ico')  # 如果有图标文件
    except:
        pass

    # 初始化程序
    app = HashTableVisualizer(root)

    # 显示初始方法说明
    app.update_method_info()

    # 启动主循环
    root.mainloop()
