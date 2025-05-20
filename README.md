# Birdy Rush – Jogo em C

**“É mais que um trabalho para ganhar pontos. É uma arte.”**

## 👨‍💻 Integrante
- **Gabriel Tenório** ([@ogabrieltenorio](https://github.com/ogabrieltenorio))  
- **Email:** gtlt@cesar.school

## 🎓 Disciplina
**Programação Imperativa e Funcional – 2025.1**  
**Instituição:** CESAR School

---

## 📋 Sobre o Projeto

**Birdy Rush** é um jogo interativo desenvolvido em linguagem C como parte da disciplina de Programação Imperativa e Funcional da CESAR School. Inspirado no clássico Flappy Bird, o jogo simula gravidade e obstáculos móveis que o jogador deve evitar com precisão e reflexo.

Foi utilizada a biblioteca **ncurses** para criar a interface no terminal, garantindo leveza e compatibilidade com sistemas Unix (Linux e macOS).

---

## 🎯 Objetivo

Aplicar na prática os principais conceitos da linguagem C:

- Estruturas de controle (`if`, `for`, `while`)
- Modularização com arquivos `.c` e `.h`
- Ponteiros e structs
- Manipulação de arquivos
- Uso da biblioteca `ncurses` para interação via terminal

---

## 🛠️ Estrutura do Projeto

```
MaisQueUmTrabalho/
├── src/           → Código-fonte (.c)
├── build/         → Binários gerados após compilação
├── Makefile       → Script para compilar automaticamente
├── LICENSE        → Licença do projeto (MIT)
└── README.md      → Este documento
```

---

## 🧠 Mecânica do Jogo

- O jogador controla um pássaro que **sobe ao pressionar a tecla espaço**
- Se nenhuma tecla for pressionada, o pássaro **cai automaticamente** pela gravidade
- Canos com buracos aparecem e se movem da direita para a esquerda
- O objetivo é **passar entre os canos** sem colidir
- O jogo termina se o pássaro:
  - Bater em um cano
  - Tocar o chão ou o teto da tela

---

## 📈 Sistema de Pontuação e Ranking

- A cada cano ultrapassado, o jogador recebe **+1 ponto**
- Cada cano tem uma flag que impede pontuação duplicada
- O jogo salva o **recorde máximo** em um arquivo externo (`recorde.txt`)
- Os **5 melhores jogadores** são armazenados e ordenados no arquivo `ranking.txt`, exibido no início e fim da partida

---

## 🎮 Controles

- **Espaço:** faz o pássaro subir
- **Gravidade:** faz o pássaro cair se nada for pressionado
- **Game Over:** ocorre ao colidir com obstáculos ou com o chão
- **Após perder:**
  - Tecla `s` permite jogar novamente
  - Qualquer outra tecla encerra o jogo

---

## 💻 Requisitos e Execução

### 1. Instale a biblioteca `ncurses`

**Ubuntu/Debian:**
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

**macOS (Homebrew):**
```bash
brew install ncurses
```

---

### 2. Clone ou acesse o projeto

```bash
cd caminho/para/o/projeto
```

### 3. Compile com o Makefile

```bash
make
```

### 4. Execute o jogo

```bash
./build/birdy_rush
```

---

## 📄 Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
