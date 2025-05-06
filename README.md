# É mais que um trabalho para ganhar pontos. É uma arte.

# Birdy Rush - Joguinho em C

## 🚀 Integrantes:
- Gabriel Tenório (@ogabrieltenorio)  
- Email: gtlt@cesar.school

## 🎓 Disciplina:
- Programação Imperativa e Funcional - 2025.1

## 🏫 Instituição:
- CESAR School

---

## 📋 Sobre o Projeto:

**Birdy Rush** é um jogo interativo desenvolvido em linguagem C como parte da disciplina de Programação Imperativa e Funcional da CESAR School. Inspirado no clássico Flappy Bird, o jogo simula a gravidade e os obstáculos por onde o jogador precisa passar com precisão e tempo de reação.

Neste projeto, foi utilizada a biblioteca **CLI-lib** para lidar com a interface via terminal, tornando o jogo leve e compatível com sistemas baseados em Unix, como Linux e macOS.

---

## 🎯 Objetivo:

O objetivo principal do projeto **Birdy Rush** é aplicar os conceitos fundamentais de programação em C, como estruturas de controle, modularização com arquivos `.h` e `.c`, além de integração com bibliotecas externas voltadas à interação por linha de comando (CLI).

---

## 🛠️ Estrutura do Projeto:

- `src/` – Arquivos de código-fonte (.c)
- `include/` – Arquivos de cabeçalho (.h)
- `build/` – Diretório para os binários gerados
- `Makefile` – Script para compilar e executar o jogo com facilidade
- `LICENSE` – Licença de uso (MIT)

---

## 🧠 Mecânica do Jogo:

No **Birdy Rush**, o jogador controla um pássaro que sobe ao pressionar a tecla **espaço**. Caso a tecla não seja pressionada, o pássaro desce naturalmente por efeito da gravidade.

Obstáculos verticais com espaços centrais se movem horizontalmente pela tela. O jogador deve passar entre esses tubos sem colidir com eles ou com o solo. Cada obstáculo superado aumenta a pontuação. O jogo termina com qualquer colisão.

---

## 💻 Requisitos e Execução:

Para compilar e executar o **Birdy Rush** em Linux ou macOS, siga os passos abaixo:

```bash
# 1. Instale a biblioteca ncurses
# Ubuntu/Debian:
sudo apt-get install libncurses5-dev libncursesw5-dev

# macOS (com Homebrew):
brew install ncurses

# 2. Vá até a pasta do projeto
cd caminho/para/o/projeto

# 3. Compile usando o Makefile
make

# 4. Execute o jogo
./build/birdy_rush

