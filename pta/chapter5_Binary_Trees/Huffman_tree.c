#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 63
#define MAX_LEN 63

// 定义哈夫曼树节点结构体
typedef struct HuffmanNode {
    int freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// 创建一个新的哈夫曼树节点
// 参数 freq 为节点代表字符的频率
// 返回值为新创建节点的指针
HuffmanNode* newNode(int freq) {
    // 为新节点分配内存
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    // 设置节点的频率
    node->freq = freq;
    // 初始化节点的左右子节点指针为 NULL
    node->left = node->right = NULL;
    return node;
}

// 构建哈夫曼树
// 参数 freq 为字符频率数组，n 为字符的数量
// 返回值为构建好的哈夫曼树的根节点指针
HuffmanNode* buildHuffmanTree(int freq[], int n) {
    // 为存储节点指针的数组分配内存
    HuffmanNode **nodes = (HuffmanNode**)malloc(n * sizeof(HuffmanNode*));
    // 为每个频率创建一个节点
    for (int i = 0; i < n; i++) {
        nodes[i] = newNode(freq[i]);
    }

    // 不断合并频率最小的两个节点，直到只剩下一个节点
    while (n > 1) {
        // 初始化最小频率节点和次小频率节点的索引
        int min1 = 0, min2 = 1;
        // 确保 min1 指向频率最小的节点，min2 指向次小的节点
        if (nodes[min1]->freq > nodes[min2]->freq) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }
        // 遍历剩余节点，更新最小和次小频率节点的索引
        for (int i = 2; i < n; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }
        // 合并最小和次小频率的节点
        HuffmanNode* merged = newNode(nodes[min1]->freq + nodes[min2]->freq);
        merged->left = nodes[min1];
        merged->right = nodes[min2];
        // 将合并后的节点放到 min1 位置
        nodes[min1] = merged;
        // 将最后一个节点放到 min2 位置，减少节点数量
        nodes[min2] = nodes[n - 1];
        n--;
    }
    // 最终剩下的节点就是哈夫曼树的根节点
    HuffmanNode* root = nodes[0];
    // 释放存储节点指针的数组的内存
    free(nodes);
    return root;
}

// 计算哈夫曼编码的最短长度
// 参数 root 为哈夫曼树的根节点指针，depth 为当前节点的深度
// 返回值为该子树对应的编码最短长度
int calcHuffmanLength(HuffmanNode* root, int depth) {
    // 如果根节点为空，返回 0
    if (root == NULL) return 0;
    // 如果是叶子节点，计算该节点对应的编码长度
    if (root->left == NULL && root->right == NULL) {
        return root->freq * depth;
    }
    // 递归计算左子树和右子树的编码长度并求和
    return calcHuffmanLength(root->left, depth + 1) + calcHuffmanLength(root->right, depth + 1);
}

// 释放哈夫曼树所占用的内存
// 参数 root 为哈夫曼树的根节点指针
void freeHuffmanTree(HuffmanNode* root) {
    // 如果根节点为空，直接返回
    if (root == NULL) return;
    // 递归释放左子树的内存
    freeHuffmanTree(root->left);
    // 递归释放右子树的内存
    freeHuffmanTree(root->right);
    // 释放当前节点的内存
    free(root);
}

// 检查给定的编码集是否为前缀码
// 参数 codes 为编码数组，n 为编码的数量
// 返回值为 1 表示是前缀码，0 表示不是
int isPrefixCode(char codes[][MAX_LEN + 1], int n) {
    // 遍历每一个编码
    for (int i = 0; i < n; i++) {
        // 与其他编码进行比较
        for (int j = 0; j < n; j++) {
            // 如果 i 不等于 j 且一个编码是另一个编码的前缀
            if (i != j && strstr(codes[j], codes[i]) == codes[j]) {
                return 0;
            }
        }
    }
    return 1;
}

// 计算给定编码集的总长度
// 参数 freq 为字符频率数组，codes 为编码数组，n 为字符的数量
// 返回值为编码集的总长度
int calcCodeLength(int freq[], char codes[][MAX_LEN + 1], int n) {
    int len = 0;
    // 遍历每个字符
    for (int i = 0; i < n; i++) {
        // 计算该字符的编码长度乘以频率，并累加到总长度中
        len += freq[i] * strlen(codes[i]);
    }
    return len;
}

int main() {
    int n;
    char chars[MAX_N];
    int freq[MAX_N];
    // 读取字符的数量
    scanf("%d", &n);
    // 读取每个字符及其频率
    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &chars[i], &freq[i]);
    }

    // 构建哈夫曼树
    HuffmanNode* root = buildHuffmanTree(freq, n);
    // 计算哈夫曼编码的最短长度
    int minLength = calcHuffmanLength(root, 0);
    // 释放哈夫曼树的内存
    freeHuffmanTree(root);

    int m;
    // 读取待检查的编码集的数量
    scanf("%d", &m);
    // 遍历每个待检查的编码集
    for (int i = 0; i < m; i++) {
        char codes[MAX_N][MAX_LEN + 1];
        // 读取每个字符对应的编码
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c %s", &c, codes[j]);
        }
        // 检查编码集是否为前缀码且总长度是否等于最短长度
        if (isPrefixCode(codes, n) && calcCodeLength(freq, codes, n) == minLength) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}