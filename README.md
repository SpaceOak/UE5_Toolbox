# UE5 Material Audit Utility

**Instant audit and analysis of materials in Unreal Engine 5 projects.  
Built for ArchViz, TechArt, and anyone tired of hunting material issues by hand.**

![demo-gif-or-screenshot-here](demo.gif)

---

## ✨ Features

- **One-click audit** of all materials in your project or current scene  
- **Interactive filtering** by:
  - Shader instruction count (Pixel/Vertex)
  - Domain (Surface, Deferred Decal, etc.)
  - Blend Mode (Opaque, Masked, Translucent, etc.)
  - Shading Model (DefaultLit, Unlit, etc.)
- **See stats at a glance** for every material — without opening the Material Editor
- **Double-click** any material to jump right to it in the Content Browser or open it for editing
- Works out-of-the-box as an Editor Utility Widget (no code changes to your project)

---

## 🔥 Motivation

Working with large ArchViz or production scenes in UE5, I constantly ran into these issues:
- No way to quickly find heavy/complex materials
- Impossible to audit hundreds of assets by hand
- Always re-inventing workflows just to understand someone else’s project

So I built this tool to automate the whole process —  
it’s already saved me hours on client projects and content cleanups.

---

## 🚀 Getting Started

1. **Clone or download** this repo to your `/Plugins/` folder:
    ```
    YourProject/Plugins/UE5_Toolbox_MatAudit/
    ```
2. **(Re)start Unreal Engine 5** (5.1+ recommended)
3. In the main editor, go to **Tools → UE5 Toolbox → Material Audit** (or open the `W_Audit_Materials` Editor Utility Widget)
4. Use the sidebar to filter, analyze, and jump to any material in your project

---

## 📺 Demo

[![Demo Video][([https://img.youtube.com/vi/YOUR_DEMO_VIDEO_ID/0.jpg](https://www.youtube.com/watch?v=0ztCDHkvbMg))](Demo)](https://www.youtube.com/watch?v=0ztCDHkvbMg)

---

## 🛠️ How it works

- Audits all UMaterial and UMaterialInstance assets via AssetRegistry
- Gathers full stats (shader instructions, blend mode, shading model, domain, etc.)
- Results shown in a fast searchable ListView with Details panel and filters
- Click or double-click to sync/open any material in the editor

---

## 📝 Roadmap

- [ ] Filter by materials **in current scene** only
- [ ] Multi-selection and bulk actions
- [ ] Advanced reporting/export
- [ ] UI polish (search, sort, dark/light theme)
- [ ] Community suggestions!

---

## 💬 Feedback & Contributions

Pull requests and feedback welcome!  
If you use this in your workflow or want to help develop it further, feel free to reach out.

---

## ⚡ Credits

Created by [YOUR_NAME](https://www.linkedin.com/in/YOUR_PROFILE)  
Inspired by everyday pain in ArchViz and UE5 tech-art.

---

## License

MIT (do whatever you want, just give credit)

---

> “Don’t waste time opening hundreds of assets by hand — audit your whole project in seconds.”
