#!/usr/bin/python
import wx
app = wx.App()
win = wx.Frame(None, title = "simple editor")
loadbtn = wx.Button(win, label = "open")
savebtn = wx.Button(win, label = "save")
win.Show()
app.MainLoop()
