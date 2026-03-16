# Jogo da Forca em C 

<div align="right">
  🇧🇷 Português | <a href="./README-en.md">🇺🇸 English</a>
</div>
<br>

<div align="center">
  <img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Windows" />
  <img src="https://img.shields.io/badge/Code::Blocks-414141?style=for-the-badge&logo=codeblocks&logoColor=white" alt="CodeBlocks" />
</div>
<br>

Bem-vindo! Este repositório guarda um projeto muito especial: meu primeiro grande desenvolvimento prático, construído durante o meu primeiro ano de faculdade em 2023. 

## 🎯 Sobre o Projeto

O foco principal desta aplicação foi integrar diferentes fundamentos da programação em um jogo funcional, divertido e interativo. Para a época, foi um grande desafio sair da clássica "tela preta do console" e dar vida a uma aplicação com interface rica, dados persistentes e efeitos de áudio nativos.

## ✨ Funcionalidades Principais

* **Interface Gráfica (GUI):** Telas, menus interativos e a renderização visual do boneco na forca a cada erro, facilitando a navegação e a experiência do jogador.
* **Manipulação de Arquivos (I/O):** Sistema de leitura e escrita de dados em arquivos de texto. Utilizado para gerenciar o banco de palavras do jogo (permitindo adicionar novas palavras sem mexer no código) e/ou salvar o histórico de pontuações.
* **Sistema de Sons:** Efeitos sonoros integrados nativamente para fornecer feedback auditivo durante os acertos, erros e ao final da partida (vitória ou derrota).

## ⚠️ Requisitos e Avisos Importantes

Devido às bibliotecas utilizadas na época do desenvolvimento para manipular a parte gráfica e de áudio em C puro, este projeto possui restrições específicas de ambiente:

* **Sistema Operacional:** Funciona **exclusivamente no Windows**. O código utiliza bibliotecas nativas e chamadas do sistema (como manipulação de som e console do Windows) que não são compatíveis com Linux ou macOS.
* **IDE Recomendada:** O projeto foi originalmente escrito e configurado utilizando o **Code::Blocks**. Para evitar problemas de vinculação de bibliotecas (linkagem), é altamente recomendado abri-lo e compilá-lo por lá.

## 💻 Como executar

1. Clone o repositório para a sua máquina:
   ```bash
   git clone https://github.com/Gabriel-E-S/JogoDaForcaEmLinguagemC.git
   ```