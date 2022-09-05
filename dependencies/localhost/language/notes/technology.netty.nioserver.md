---
id: yyv09daxwwscwmn6jrtl76e
title: Nioserver
desc: ''
updated: 1662362054734
created: 1662361748570
---
```java{.line-numbers, highlight=[33,50,85-91,101]}
package com.handrpc.transport;

import javafx.scene.control.TableRow;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;

/**
 * @Author: Virgil Lee
 * @Date: 2022/09/05/14:08
 * @Description:
 */
public class MultiplexerTimeServer implements Runnable{

    private Selector selector;

    private ServerSocketChannel serverSocketChannel;

    private volatile boolean stop;

    public MultiplexerTimeServer(int port) {
        try {
            selector = Selector.open();
            serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.socket().bind(new InetSocketAddress(port), 1024);
            // 监听selectionkey的accept操作位
            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
            System.out.println("the tiem server is start");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public void stop(){
        this.stop = true;
    }

    @Override
    public void run() {
        while(!stop){
            // 每1s进行选择一次
            try {
                selector.select(1000);
                Set<SelectionKey> keys = selector.keys();
                Iterator<SelectionKey> iterator = keys.iterator();
                SelectionKey key = null;
                while(iterator.hasNext()){
                    key = iterator.next();
                    iterator.remove();
                    try {
                        handleInput(key);
                    } catch (IOException e) {
                        if(key.channel() != null){
                            key.channel().close();
                        }
                    }

                }
            } catch (Throwable t) {
                t.printStackTrace();
            }
        }
        // 多路复用器关闭后，所有注册在上面的Channel和Pipe等资源都会被自动去注册并关闭，所以不需要重复释放资源
        if(selector != null){
            try {
                selector.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void handleInput(SelectionKey key) throws IOException {
        if(key.isValid()){
            // 处理新接入的请求消息
            if(key.isAcceptable()) {
                // accept the new connection
                ServerSocketChannel channel = (ServerSocketChannel) key.channel();
                // tcp连接建立
                SocketChannel sc = channel.accept();
                // 设置channel为异步非阻塞
                sc.configureBlocking(false);
                // add the new connection to the selector
                sc.register(selector, SelectionKey.OP_READ);
            }
            if(key.isReadable()){
                // read the data
                SocketChannel sc = (SocketChannel) key.channel();
                ByteBuffer readBuffer = ByteBuffer.allocate(1024);
                int readBytes = sc.read(readBuffer);
                // channel为异步非阻塞 读的情况有三种情况 0(正常场景), >0(读了一些，还没读完), -1(连接关闭)
                if(readBytes > 0) {
                    // 将当前limit设置为position为0
                    readBuffer.flip();
                    byte[] bytes = new byte[readBuffer.remaining()];
                    readBuffer.get(bytes);
                    String body = new String(bytes, "UTF-8");
                    System.out.println("the time sever receive order: " + body);
                    String currentTime = "query time order".equalsIgnoreCase(body) ? new Date(System.currentTimeMillis()).toString() : "bad order";
                    doWrite(sc, currentTime);
                }else if(readBytes < 0){
                    // 对端链路关闭
                    key.cancel();
                    sc.close();
                }else{
                    ;
                }
            }
        }
    }

    private void doWrite(SocketChannel channel, String response) throws IOException{
        if(response != null && response.trim().length() > 0){
            byte[] bytes = response.getBytes();
            ByteBuffer writeBuffer = ByteBuffer.allocate(bytes.length);
            writeBuffer.put(bytes);
            writeBuffer.flip();
            channel.write(writeBuffer);
        }
    }
}
```