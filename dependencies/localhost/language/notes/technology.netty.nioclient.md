---
id: 1w4a2mbi7jyqkmpfcffqhh9
title: Nioclient
desc: ''
updated: 1662370820947
created: 1662366832751
---
```java{.line-numbers, hightlights=[115-119]}
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectableChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.Iterator;
import java.util.Set;

public class TimeClient implements Runnable{

    private String host;
    private int port;
    private SocketChannel sc;
    private Selector selector;
    private volatile boolean stop;

    public TimeClient(String host, int port){
        this.host = host == null ? "127.0.0.1" : host;
        this.port = port;
        try {
            selector = Selector.open();
            sc = SocketChannel.open();
            sc.configureBlocking(false);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    @Override
    public void run() {
        try {
            doConnect();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        while(!stop){
            try {
                selector.select(1000);
                SelectionKey key = null;
                Set<SelectionKey> keys = selector.keys();
                Iterator<SelectionKey> it = keys.iterator();

                while(it.hasNext()){
                    key = it.next();
                    it.remove();
                    try {
                        doInputHandle(key);
                    }catch (IOException e){
                        if(key != null){
                            key.cancel();
                            if(key.channel() != null){
                                key.channel().close();
                            }
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

        }

        if(selector != null){
            try{
                selector.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }

    private void doInputHandle(SelectionKey selectionKey) throws IOException{
        if(selectionKey.isValid()){
            SocketChannel socketChannel = (SocketChannel)selectionKey.channel();
            if(selectionKey.isConnectable()){
                if(socketChannel.finishConnect()){
                    socketChannel.register(selector, SelectionKey.OP_READ);
                    doWrite(socketChannel);
                }else{
                    System.exit(1);
                }
            }

            if(selectionKey.isReadable()){
                ByteBuffer readBuffer = ByteBuffer.allocate(1024);
                int readBytes = socketChannel.read(readBuffer);
                if(readBytes > 0){
                    readBuffer.flip();
                    byte[] bytes = new byte[readBuffer.remaining()];
                    // 从buffer读入字节数组
                    readBuffer.get(bytes);
                    String body = new String(bytes);
                    System.out.println("now is : " + body);
                    this.stop = true;
                }else if(readBytes < 0){
                    // 对端连接关闭
                    selectionKey.cancel();
                    socketChannel.close();
                }else{
                    ;
                }
            }
        }
    }

    private void doConnect() throws IOException{
        // 如果直接连接成功，则注册到多路复用器上，发送请求消息，读应答等
        if(sc.connect(new InetSocketAddress(host, port))){
            sc.register(selector, SelectionKey.OP_READ);
            doWrite(sc);
        }else{
            sc.register(selector, SelectionKey.OP_CONNECT);
        }
    }

    private void doWrite(SocketChannel sc) throws IOException{
        byte[] req = "quer time order".getBytes();
        // 注册到selector中，selectionKey标志位read
        ByteBuffer writeBufer = ByteBuffer.allocate(req.length);
        writeBufer.put(req);
        writeBufer.flip();
        // sc异步非阻塞去写
        sc.write(writeBufer);
        if(!writeBufer.hasRemaining()){
            System.out.println("send succeed");
        }
    }
}
```

> ![](/assets/images/2022-09-05-17-07-49.png)
>![](/assets/images/2022-09-05-17-36-57.png)
