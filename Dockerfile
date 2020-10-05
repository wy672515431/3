FROM gcc:latest
WORKDIR /app/
COPY ./* ./
RUN gcc program.c -o program
RUN chmod +x program