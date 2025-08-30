package com.example.anti_lossdevice.bean;

public class Send {
    private Integer cmd;
    private Integer open;

    public void setHeart(Integer heart) {
        this.heart = heart;
    }

    private Integer heart;

    @Override
    public String toString() {
        return "Send{" +
                "cmd=" + cmd +
                ", open=" + open +
                ", open=" + heart +
                '}';
    }

    public Integer getCmd() {
        return cmd;
    }

    public void setCmd(Integer cmd) {
        this.cmd = cmd;
    }

    public Integer getOpen() {
        return open;
    }

    public void setOpen(Integer open) {
        this.open = open;
    }
}
