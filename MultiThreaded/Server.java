import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Consumer;

public class Server{

    public Consumer<Socket> getConsumer(){
        return (clientSocket) -> {
            try {
                PrintWriter toClient = new PrintWriter(clientSocket.getOutputStream(), true); // Enable auto-flush
                toClient.println("Hello from the server!!");
                toClient.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        };
    }
    

    public static void main(String[] args) {
        int port=8081;
        Server server=new Server();
        try {
            ServerSocket serverSocket=new ServerSocket(port);
            serverSocket.setSoTimeout(10000); // 10 sec
            System.out.println("Server started and listening on port" + port);
            // now listening for connections:-
            while(true){
                Socket acceptedSocket=serverSocket.accept(); // accepted the connection from client
                // threading concept starts here:-
                Thread thread=new Thread(()->server.getConsumer().accept(acceptedSocket));
                thread.start();
            }
        } catch (Exception e) {
            // TODO: handle exception
            e.printStackTrace();
        }
    }
}