package com.example.anti_lossdevice.bean;

public class Receive {
    private String log;
    private String lat;
    private String heart;
    private String waning;
    private String open;

    @Override
    public String toString() {
        return "Receive{" +
                "log='" + log + '\'' +
                ", lat='" + lat + '\'' +
                ", heart='" + heart + '\'' +
                ", waning='" + waning + '\'' +
                ", open='" + open + '\'' +
                '}';
    }

    public String getLog() {
        return log;
    }

    public void setLog(String log) {
        this.log = log;
    }

    public String getLat() {
        return lat;
    }

    public void setLat(String lat) {
        this.lat = lat;
    }

    public String getHeart() {
        return heart;
    }

    public void setHeart(String heart) {
        this.heart = heart;
    }

    public String getWaning() {
        return waning;
    }

    public void setWaning(String waning) {
        this.waning = waning;
    }

    public String getOpen() {
        return open;
    }

    public void setOpen(String open) {
        this.open = open;
    }
}
