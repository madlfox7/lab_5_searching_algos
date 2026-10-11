FROM gcc:13 AS builder

WORKDIR /app
COPY main.cpp .

RUN g++ -O2 -static-libstdc++ -static-libgcc -o myapp main.cpp

FROM debian:bookworm-slim

COPY --from=builder /app/myapp /usr/local/bin/myapp

CMD ["myapp"]
