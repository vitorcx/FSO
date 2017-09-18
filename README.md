# FSO - Fundamentos de Sistemas Operacionais.

## Histórico
O sistema operacional é o software que tem o papel de tornar o gerenciamento dos recursos de hardware mais simples e fácil para os programas de usuário.  
O sistema operacional opera no modo núcleo do computador, aonde tem acesso completo ao hardware. Os demais softwares operam no modo usuário, aonde possuem acesso a um conjunto limitado de intruções.

1ª Geração: Os computadores estavam em um nível ainda muito primitivo. Ainda não existiam sistemas operacionais.  

2ª Geração: Sistemas de Lotes (batch) e jobs. Um computador recebia os artefatos de entrada, executavam e produziam a saida para as entradas fornecidas. Um novo job só era iniciado ao final do job anterior. Os sistemas operacionais tipicos eram o Fortran Monitor System e o IBSYS, que basicamente operavam o ciclo de jobs num sistema de lotes.  

3ª Geração: Os sistemas operacionais desta geração como o OS/360 tinham que atender varios perfis de usuários e funcionalidades. Nesta geração os sistemas operacionais passaram a introduzir a tecnica da multipgrogramação. A memoria era dividida em varias partições com um job em cada partição. Enquanto um job espera alguma operação de E/S, os algum outro poderia utilizar a CPU, fazendo com que a CPU seja utilizada quase 100% do tempo. Tambem foi introduzida a tecnica chamada Spooling, na qual os job em cartão perfurado ja eram lidos diretamente para o disco. Uma modalidade de multiprogramação tambem introduzida nesta geração era o conceito de tempo compartilhado, no qual diferentes usuários utilizam terminais diferentes online, e a CPU poderia ser alocada apenas para os jobs que requerem mais processamento.  
Inicio do sistema UNIX, foi elaborado tambem um padrão chamado POSIX, que define uma interface minima de chamadas de sistema que sistemas compativeis com o UNIX devem suportar.  

4ª Geração: Surgimento dos Computadores Pessoais. Computadores pessoais de maior porte utilizados em negocios eram chamados de estações de trabalho. Dois sistemas operacionais dominam o mercado, MS-DOS e UNIX.  
Inicio do desenvolvimento de sistemas operacionais de rede e sistemas operacionais distribuidos. Em sistemas de rede cada computador executa o sistema localmente, e tem ciencia da existencia dos outros computadores, podem se conectar e baixar arquivos deles. Sistemas distribuidos são aqueles que aparecem para o usuário como um sistema monoprocessado tradicional.

## Processos e Threads
