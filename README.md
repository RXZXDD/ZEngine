# ZEngine
---
## Description
This project is a toy for learning and practicing how to building a game enigne.

Some using habits will like Unreal Engine.

## Current Features
<details>
<summary>Memory Management</summary>

- Using Mimalloc as the default memory allocator.

</details>


<details>

<summary>Log System</summary>

- Single-Threaded.
- 3 Output devices: Console, File, Log-Tab in Editor.
- Easy Using: `ZLog(Default, Display, "Message: %s", your messages);`
- Easy Extension: 
	- You can create your own output device by inheriting `ZLogOutputDevice` and override `Serialize` function.
	- You can add your custom logger by using Macros:`DECLARE_LOGGER_EXTERN`, `DEFINE_LOGGER`

</details>

<details>
<summary>Rendering</summary>

- Using `SceneRenderer` calss to render the scene.
- inherate `IDrawable` interface for all renderable objects

</details>

<details>
<summary>RHI Layer abstraction</summary>

- Using D3D12 as the default RHI API.
- Details in [RHI](./ZEngine/Core/RHI) folder.

</details>

<details>
<summary>UI System</summary>

- Using ImGui as the UI library.
- Having Abstract UI Class for ImGui:`LogTab`,`Viewport`

</details>

---

# TODO
- what will do next: see [TODO.md](./todo.md)
- what mark todo: search `todo`/`TODO` in solutions