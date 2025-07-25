# Aura Music Player

<img width="1280" height="800" alt="image" src="https://github.com/user-attachments/assets/624e22fe-4197-4430-b675-fb46c1ca0efd" />

**Aura Music Player** 是一款使用 **C++** 和 **Qt** 框架构建的现代化、界面精美的桌面音乐播放器。项目旨在复刻市场上主流音乐播放器的核心功能，并提供一个拥有高级感和流畅用户体验的界面。

本项目作为 Qt UI/UX 设计与开发的学习实践项目。

---

## ✨ 项目亮点 (Features)

- **现代化的 UI/UX 设计**: 
  - 采用**暗色主题**，营造沉浸式听觉氛围。
  - **无边框窗口**设计，配合自定义阴影和圆角，实现极致的视觉整体感。
  - **动态交互效果**: 列表项、音乐卡片的悬停效果，配以平滑的过渡动画。
  - **自定义控件**: 完全使用 QSS 和 C++ 绘制技术美化的滚动条、按钮和进度条。

- **核心播放功能**:
  - **本地音乐管理**: 扫描并播放本地音乐文件。
  - **播放列表**: 创建、管理和保存自定义播放列表。
  - **音乐收藏**: 一键收藏你喜爱的歌曲。
  - **历史记录**: 自动记录最近播放的歌曲。
  - **持久化存储**：SQLite持久化存储数据

- **丰富的界面模块**:
  - **发现音乐**: 采用卡片式布局，展示推荐专辑和歌单。
  - **我喜欢/本地音乐**: 清晰的列表视图，展示歌曲详细信息。
  - **播放控制条**: 集成了播放/暂停、上一首/下一首、播放进度控制等核心功能。
  - **歌曲信息展示**：展示歌曲名以及歌手信息还有专辑图片。
  - **音量控制模块**：通过点击或者拖拽的方法调节音量

---

## 🛠️ 技术栈 (Technology Stack)

- **核心框架**: **Qt 6 / Qt 5**
- **编程语言**: **C++11**
- **UI 实现**: **Qt Widgets** (非 QML)
- **界面美化**: **QSS (Qt Style Sheets)**
- **自定义绘制**: 大量使用 **`QPainter`**, **`paintEvent`**, 和 **`QGraphicsDropShadowEffect`** 来实现自定义外观和效果。
- **项目构建**: **qmake** / **CMake** (根据你的项目选择)
- **开发环境**: **Qt Creator**

---

## 🚀 如何运行 (Getting Started)

### 依赖环境
- **Qt** (推荐版本 5.15 或更高)
- **C++ 编译器** (MSVC, GCC, Clang)
- **Qt Creator IDE** (推荐)

### 构建与运行步骤

1. **克隆项目到本地**:
   ```bash
   https://github.com/Lyuih/Aura-Music-Player.git
   ```
   <!-- 提示：请将 your-username 替换为你的 GitHub 用户名 -->

2. **使用 Qt Creator 打开项目**:
   - 打开 Qt Creator。
   - 选择 `文件 (File)` -> `打开文件或项目 (Open File or Project...)`。
   - 导航到克隆下来的项目文件夹，选择 `.pro` 文件并打开。

3. **配置项目**:
   - Qt Creator 会自动提示你配置项目。选择一个你已经安装好的 Qt Kit (例如, `Desktop Qt 5.15.2 MSVC2019 64bit`)。
   - 点击 `配置项目 (Configure Project)`。

4. **构建并运行**:
   - 点击 Qt Creator 左下角的 **绿色三角形“运行”按钮**，或者使用快捷键 `Ctrl + R`。
   - 程序将会被编译并启动。

---

## 🖼️ 界面截图 (Screenshots)




| 发现音乐 | 我喜欢 | 播放控制 |
| :---: | :---: | :---: |
| <img width="1280" height="800" alt="image" src="https://github.com/user-attachments/assets/5049903d-60ed-42e4-832e-3c7337859d78" /> |<img width="1280" height="800" alt="image" src="https://github.com/user-attachments/assets/bc089f1f-53e9-4942-85a8-fe9225d5ef67" />| <img width="1280" height="800" alt="image" src="https://github.com/user-attachments/assets/2416124e-ba27-4e0e-9240-ad22c3b90173" />|

---

## 💡 项目心得与挑战

在这个项目中，我深入实践了 Qt Widgets 的高级 UI 定制技术，主要挑战和收获包括：

- **实现无边框窗口**: 通过重写 `mousePressEvent` 和 `mouseMoveEvent` 实现了窗口的拖动，并自定义了最大化、最小化和关闭按钮。
- **自定义阴影与圆角**: 采用了“双层窗口”技巧，通过一个带阴影的透明父窗口来容纳带圆角的主内容窗口，完美解决了 `QGraphicsDropShadowEffect` 和 `border-radius` 的冲突问题。
- **QSS 的深入使用**: 探索了如何通过 QSS 伪状态 (`::handle`, `::groove`) 和状态选择器 (`:hover`) 来完全自定义 `QScrollBar` 等复杂控件。
- **事件处理与自定义信号**: 通过重写 `enterEvent`, `leaveEvent` 和 `paintEvent`，为音乐卡片实现了动态的悬停遮罩效果。同时，通过自定义 `clicked()` 信号，让非按钮的自定义控件也能响应点击。
- **自定义 `QListWidget` 项**: 使用 `setItemWidget` 将自定义设计的 `QWidget` (包含了歌曲信息、时长等) 嵌入到 `QListWidget` 的每一行中，实现了高度定制化的列表。

---

## 📝 未来的计划 (Future Work)

- [ ] 实现歌词同步滚动显示功能。
- [ ] 对接第三方音乐 API，获取在线音乐资源。
- [ ] 增加主题切换功能（浅色/暗色）。
- [ ] 性能优化，特别是在加载大量本地音乐时。

---



---

## ⚖️ 许可证 (License)

本项目采用 [MIT License](LICENSE) 许可。
